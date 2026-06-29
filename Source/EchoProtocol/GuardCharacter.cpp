// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardCharacter.h"

#include "Components/WidgetComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "GuardAIController.h"
#include "GuardGaugeWidget.h"
#include "Gun.h"

// Sets default values
AGuardCharacter::AGuardCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentPatrolIndex = 0;

	// 암살 위젯
	TakeDownWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TakeDownWidgetComponent"));
	TakeDownWidgetComponent->SetupAttachment(RootComponent);
	TakeDownWidgetComponent->SetRelativeLocation(FVector(0, 0, 120.f));
	TakeDownWidgetComponent->SetVisibility(false);

	// 게이지 위젯
	GaugeWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("GaugeWidgetComponent"));
	GaugeWidgetComponent->SetupAttachment(RootComponent);
	GaugeWidgetComponent->SetRelativeLocation(FVector(0, 0, 100.f));
	GaugeWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	GaugeWidgetComponent->SetVisibility(false);
}

// Called when the game starts or when spawned
void AGuardCharacter::BeginPlay()
{
	Super::BeginPlay();

	GuardGaugeWidget = Cast<UGuardGaugeWidget>(GaugeWidgetComponent->GetUserWidgetObject());

}

// Called every frame
void AGuardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Speed = GetVelocity().Size2D();
	UpdateSightGauge(DeltaTime);
}

// Called to bind functionality to input
void AGuardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

AActor* AGuardCharacter::GetCurrentPatrol() const
{
	if (!PatrolPoints.IsValidIndex(CurrentPatrolIndex))
	{
		return nullptr;
	}

	return PatrolPoints[CurrentPatrolIndex];
}

float AGuardCharacter::GetSpeed() const
{
	return Speed;
}

void AGuardCharacter::TakeDown()
{
	AAIController* AIController = Cast<AAIController>(GetController());
	AIController->StopMovement();
	UBrainComponent* BrainComponent = AIController->GetBrainComponent();
	BrainComponent->StopLogic(TEXT("TakeDown"));
	SetActorEnableCollision(false);
	PlayAnimMontage(DownMontage);
}

void AGuardCharacter::HandleDeath()
{
	Super::HandleDeath();
	Destroy();
}

int32 AGuardCharacter::GetCurrentPatrolIndex() const
{
	return CurrentPatrolIndex;
}

void AGuardCharacter::AdvancePatrolIndex()
{
	CurrentPatrolIndex++;

	if (CurrentPatrolIndex >= PatrolPoints.Num())
	{
		CurrentPatrolIndex = 0;
	}
}

void AGuardCharacter::SetTakeDownWidget(bool bIsVisible)
{
	TakeDownWidgetComponent->SetVisibility(bIsVisible);
}

void AGuardCharacter::PullTrigger()
{
	if (!Weapon)
	{
		return;
	}
	PlayAnimMontage(ShootMontage);
	Weapon->Fire();
}


float AGuardCharacter::GetSightGauge() const
{
	return SightGauge / MaxSightGauge;
}

void AGuardCharacter::UpdateSightGauge(float DeltaTime)
{
	if (!GuardGaugeWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("GuardGaugeWidget null"));

		return;
	}

	AGuardAIController* GuardAiController = Cast<AGuardAIController>(GetController());
	if (!GuardAiController)
	{
		UE_LOG(LogTemp, Error, TEXT("GuardAiController null"));

		return;
	}

	if (!GuardAiController->GetCanSeePlayer())
	{
		GaugeWidgetComponent->SetVisibility(false);
		SightGauge = 0;
		GuardGaugeWidget->SetSightGauge(SightGauge / MaxSightGauge);
		return;
	}

	if (SightGauge >= MaxSightGauge)
	{
		UE_LOG(LogTemp, Error, TEXT("플레이어 감지!!!"));
		return;
	}

	GaugeWidgetComponent->SetVisibility(true);
	SightGauge += DeltaTime * 10;
	GuardGaugeWidget->SetSightGauge(SightGauge / MaxSightGauge);
}

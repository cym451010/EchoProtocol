// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardCharacter.h"

#include "AIController.h"
#include "BrainComponent.h"

// Sets default values
AGuardCharacter::AGuardCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentPatrolIndex = 0;
}

// Called when the game starts or when spawned
void AGuardCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGuardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Speed = GetVelocity().Size2D();

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
	UE_LOG(LogTemp, Warning, TEXT("가드 애니메이션 실행"));

	AAIController* AIController = Cast<AAIController>(GetController());
	AIController->StopMovement();
	UBrainComponent* BrainComponent = AIController->GetBrainComponent();
	BrainComponent->StopLogic(TEXT("TakeDown"));
	SetActorEnableCollision(false);
	PlayAnimMontage(DownMontage);
}

void AGuardCharacter::Dead()
{
	Destroy();
}

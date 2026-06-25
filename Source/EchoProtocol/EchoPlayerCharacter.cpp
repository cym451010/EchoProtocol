// Fill out your copyright notice in the Description page of Project Settings.


#include "EchoPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Gun.h"
#include "DrawDebugHelpers.h"
#include "KismetTraceUtils.h"
#include "Engine/World.h"
#include "GuardCharacter.h"

//TODO :  앉아쏘기 애니메이션 추가하기 (없음..)

// Sets default values
AEchoPlayerCharacter::AEchoPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Character Rotation 설정 (TPS 게임)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Can Crouch 켜기
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

}

// Called when the game starts or when spawned
void AEchoPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		return;
	}

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!Subsystem)
	{
		return;
	}
	Subsystem->AddMappingContext(DefaultMappingContext, 0);

	GetWorldTimerManager().SetTimer(LineTraceTimerHandle, this, &AEchoPlayerCharacter::TraceInteractable, 0.3f, true);
}

// Called every frame
void AEchoPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Speed = GetVelocity().Size2D();

}

// Called to bind functionality to input
void AEchoPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (!EnhancedInput)
	{
		return;
	}

	EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEchoPlayerCharacter::Move);
	EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEchoPlayerCharacter::Look);
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AEchoPlayerCharacter::Jump);
	EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AEchoPlayerCharacter::StartCrouch);
	EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AEchoPlayerCharacter::StopCrouch);
	EnhancedInput->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AEchoPlayerCharacter::StartSprint);
	EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &AEchoPlayerCharacter::StopSprint);
	EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &AEchoPlayerCharacter::Interact);
	EnhancedInput->BindAction(FireAction, ETriggerEvent::Started, this, &AEchoPlayerCharacter::Fire);
	EnhancedInput->BindAction(AimAction, ETriggerEvent::Triggered, this, &AEchoPlayerCharacter::StartAim);
	EnhancedInput->BindAction(AimAction, ETriggerEvent::Completed, this, &AEchoPlayerCharacter::StopAim);

}

void AEchoPlayerCharacter::Move(const struct FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (!Controller)
	{
		return;
	}

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AEchoPlayerCharacter::Look(const struct FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AEchoPlayerCharacter::Jump()
{
	Super::Jump();
}

void AEchoPlayerCharacter::StartCrouch(const struct FInputActionValue& Value)
{
	bCrouch = Value.Get<bool>();
	Crouch(bCrouch);
}

void AEchoPlayerCharacter::StopCrouch(const struct FInputActionValue& Value)
{
	bCrouch = Value.Get<bool>();
	UnCrouch();
}

void AEchoPlayerCharacter::Crouch(bool bClientSimulation)
{
	if (bIsAim)
	{
		return;
	}

	Super::Crouch(bClientSimulation);
}

void AEchoPlayerCharacter::UnCrouch(bool bClientSimulation)
{
	Super::UnCrouch(bClientSimulation);
}

void AEchoPlayerCharacter::StartSprint(const struct FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AEchoPlayerCharacter::StopSprint(const struct FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AEchoPlayerCharacter::Interact(const struct FInputActionValue& Value)
{
	if (bHasInteractable)
	{
		TryTakeDown();
	}
}

void AEchoPlayerCharacter::TraceInteractable()
{
	FVector Location;
	FRotator Rotation;
	Controller->GetPlayerViewPoint(Location, Rotation);
	FVector Start = Location;
	FVector End = Start + (Rotation.Vector() * MaxTraceRange);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	//DebugLineTrace(Start, End, bHit, HitResult);

	AGuardCharacter* NewGuard = bHit ? Cast<AGuardCharacter>(HitResult.GetActor()) : nullptr;

	if (Guard && Guard != NewGuard)
	{
		Guard->SetTakeDownWidget(false);
	}

	Guard = NewGuard;
	bHasInteractable = (Guard != nullptr);

	if (Guard)
	{
		Guard->SetTakeDownWidget(true);
	}
}

void AEchoPlayerCharacter::DebugLineTrace(const FVector& OutStart, const FVector& OutEnd, const bool& OutHit, const FHitResult& OutHitResult) const
{
	DrawDebugLineTraceSingle(GetWorld(), OutStart, OutEnd, EDrawDebugTrace::Persistent, OutHit, OutHitResult, FColor::Red, FColor::Green, 2.f);
}

float AEchoPlayerCharacter::GetSpeed() const
{
	return Speed;
}

void AEchoPlayerCharacter::TryTakeDown()
{
	DisableInput(PlayerController);
	//TODO : 암살 구현하기
	if (!Guard)
	{
		return;
	}
	FVector TakeDownVector = Guard->GetActorLocation() - GetActorLocation();
	TakeDownVector.Normalize();

	float Dot = FVector::DotProduct(Guard->GetActorForwardVector(), TakeDownVector);

	if (Dot > 0.75f && bHit)
	{
		FVector BackOffset = -Guard->GetActorForwardVector() * TakeDownRange;
		FVector RightOffset = Guard->GetActorRightVector() * TakeDownRightRange;

		FVector TargetLocation = Guard->GetActorLocation() + BackOffset + RightOffset;
		SetActorLocation(TargetLocation);
		SetActorRotation(Guard->GetActorRotation());
		PlayerController->SetControlRotation(Guard->GetActorRotation());

		bIsPerformingTakeDown = true;
		PlayAnimMontage(TakeDownMontage);

		Guard->TakeDown();
	}
}

void AEchoPlayerCharacter::EndTakeDown()
{
	EnableInput(PlayerController);
	bIsPerformingTakeDown = false;
}

void AEchoPlayerCharacter::Fire(const struct FInputActionValue& Value)
{
	if (!Weapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Null"));

		return;
	}

	if (!bIsAim)
	{
		return;
	}
	Weapon->Fire();
}

void AEchoPlayerCharacter::HandleDeath()
{
	UE_LOG(LogTemp, Error, TEXT("플레이어 사망"));
}

void AEchoPlayerCharacter::StartAim(const struct FInputActionValue& Value)
{
	if (bIsPerformingTakeDown)
	{
		return;
	}

	if (bCrouch)
	{
		return;
	}

	bIsAim = Value.Get<bool>();
}

void AEchoPlayerCharacter::StopAim(const struct FInputActionValue& Value)
{
	if (bIsPerformingTakeDown)
	{
		return;
	}
	
	bIsAim = Value.Get<bool>();
}

bool AEchoPlayerCharacter::GetbAim() const
{
	return bIsAim;
}

float AEchoPlayerCharacter::GetHp() const
{
	return CurrentHealth / MaxHealth;
}
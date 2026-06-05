// Fill out your copyright notice in the Description page of Project Settings.


#include "EchoPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEchoPlayerCharacter::AEchoPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
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
}

// Called every frame
void AEchoPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AEchoPlayerCharacter::StartCrouch);
	EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AEchoPlayerCharacter::StopCrouch);
}

void AEchoPlayerCharacter::Move(const struct FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	if (!Controller)
	{
		return;
	}

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

void AEchoPlayerCharacter::StartCrouch(const struct FInputActionValue& Value)
{
	bool bCrouch = Value.Get<bool>();
	Crouch(bCrouch);
}

void AEchoPlayerCharacter::StopCrouch(const struct FInputActionValue& Value)
{
	UnCrouch();
}

void AEchoPlayerCharacter::Crouch(bool bClientSimulation)
{
	Super::Crouch(bClientSimulation);

	//UE_LOG(LogTemp, Warning, TEXT("ClientSimulation : %s"), bClientSimulation ? TEXT("True") : TEXT("False"));
}

void AEchoPlayerCharacter::UnCrouch(bool bClientSimulation)
{
	Super::UnCrouch(bClientSimulation);

	//UE_LOG(LogTemp, Warning, TEXT("ClientSimulation : %s"), bClientSimulation ? TEXT("True") : TEXT("False"));
}

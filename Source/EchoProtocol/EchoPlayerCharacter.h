// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EchoPlayerCharacter.generated.h"

UCLASS()
class ECHOPROTOCOL_API AEchoPlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEchoPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	float GetSpeed() const;
	UFUNCTION(BlueprintCallable)
	void EndTakeDown();
protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	void StartCrouch(const struct FInputActionValue& Value);
	void StopCrouch(const struct FInputActionValue& Value);
	void StartSprint(const struct FInputActionValue& Value);
	void StopSprint(const struct FInputActionValue& Value);
	void Interact(const struct FInputActionValue& Value);
	void Fire(const struct FInputActionValue& Value);

	void Crouch(bool bClientSimulation = false) override;
	void UnCrouch(bool bClientSimulation = false) override;
	bool TraceInteractable();
	void DebugLineTrace(const FVector& OutStart, const FVector& OutEnd, const bool& OutHit, const FHitResult& OutHitResult) const;
	void TryTakeDown();
	
	virtual void HandleDeath() override;

	//Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	//Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> CrouchAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> SprintAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> FireAction;

	UPROPERTY(Category = "Character Movement: Walking", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))
	float WalkSpeed = 600;
	UPROPERTY(Category = "Character Movement: Sprinting", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))
	float SprintSpeed = 900;

private:
	FHitResult HitResult;
	UPROPERTY(EditAnywhere)
	float MaxTraceRange;
	float Speed;
	UPROPERTY(EditAnywhere)
	float TakeDownRange = 100.f;
	bool bIsPerformingTakeDown = false;

	// Weapon
	UPROPERTY(EditAnywhere, Category = "Gun")
	TSubclassOf<class AGun> WeaponClass;
	UPROPERTY(EditAnywhere, Category = "Gun")
	class AGun* Weapon;

	//Animation
	UPROPERTY(EditAnywhere, Category = "Animation")
	class UAnimMontage* TakeDownMontage;
};

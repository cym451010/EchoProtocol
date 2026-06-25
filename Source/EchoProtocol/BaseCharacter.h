// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ECHOPROTOCOL_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleDeath();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

protected:
	// Weapon
	UPROPERTY(EditAnywhere, Category = "Gun")
	TSubclassOf<class AGun> WeaponClass;
	UPROPERTY(EditAnywhere, Category = "Gun")
	class AGun* Weapon;

	// SFX
	UPROPERTY(EditAnywhere, Category = "SFX")
	class USoundBase* WalkSound;

	void PlayWalkSound();

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100.f;
	float CurrentHealth;
};

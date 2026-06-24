// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Gun.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!WeaponClass)
	{
		return;
	}
	Weapon = GetWorld()->SpawnActor<AGun>(WeaponClass);
	Weapon->SetOwner(this);
	Weapon->AttachToComponent(Cast<USceneComponent>(GetMesh()), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	
	OnTakeAnyDamage.AddDynamic(this, &ABaseCharacter::HandleTakeAnyDamage);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (CurrentHealth <= 0)
	{
		return;
	}

	CurrentHealth -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentHealth);

	if (CurrentHealth <= 0)
	{
		HandleDeath();
		Weapon->Destroy();
	}
}

void ABaseCharacter::HandleDeath()
{
	
}

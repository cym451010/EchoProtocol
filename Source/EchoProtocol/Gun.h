// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class ECHOPROTOCOL_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();
	void SpawnMuzzleFlash();
	AController* GetOwnerController() const;

private:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Muzzle")
	class UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, Category = "SFX")
	class USoundBase* ShootSound;
	UPROPERTY(EditAnywhere, Category = "Gun")
	float MaxRange = 1000.f;

	FHitResult HitResult;

private:
	void DebugLineTrace(const FVector& OutStart, const FVector& OutEnd, const bool& OutHit, const FHitResult& OutHitResult) const;
};

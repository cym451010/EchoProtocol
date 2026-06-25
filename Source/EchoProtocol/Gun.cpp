// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "BaseCharacter.h"
#include "KismetTraceUtils.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::Fire()
{
	SpawnMuzzleFlash();

	if (!ShootSound || !ImpactSound || !BulletHitBodySound)
	{
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(this, ShootSound, GetActorLocation());

	AController* OwnerController = GetOwnerController();
	if (!OwnerController)
	{
		return;
	}

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector Start = Location;
	FVector End = Start + (Rotation.Vector() * MaxRange);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	DebugLineTrace(Start, End, bHit, HitResult);

	if (!bHit || !HitResult.GetActor())
	{
		return;
	}

	if (ABaseCharacter* HitCharacter = Cast<ABaseCharacter>(HitResult.GetActor()))
	{
		UGameplayStatics::PlaySoundAtLocation(this, BulletHitBodySound, HitResult.ImpactPoint);
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), 10, OwnerController, this, UDamageType::StaticClass());

	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, HitResult.ImpactPoint);
	}
}

AController* AGun::GetOwnerController() const
{
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn)
	{
		return nullptr;
	}

	return Pawn->GetController();
}

void AGun::DebugLineTrace(const FVector& OutStart, const FVector& OutEnd, const bool& OutHit, const FHitResult& OutHitResult) const
{
	DrawDebugLineTraceSingle(GetWorld(), OutStart, OutEnd, EDrawDebugTrace::Persistent, OutHit, OutHitResult, FColor::Red, FColor::Green, 2.f);
}

void AGun::SpawnMuzzleFlash()
{
	if (!MuzzleFlash)
	{
		return;
	}
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, FName("MuzzleSocket"));
	UE_LOG(LogTemp, Warning, TEXT("머즐 생성"));
}

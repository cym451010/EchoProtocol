#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GuardCharacter.generated.h"

UCLASS()
class ECHOPROTOCOL_API AGuardCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AGuardCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
    // Combat
    void TakeDown();
    UFUNCTION(BlueprintCallable)
    void Dead();

public:
    // AI / Patrol
    AActor* GetCurrentPatrol() const;

    UPROPERTY(EditAnywhere, Category = "AI")
    TArray<AActor*> PatrolPoints;

    int32 CurrentPatrolIndex;

    UPROPERTY()
    class AEchoPlayerCharacter* Player;

private:
    // Animation
    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* DownMontage;

    bool bIsPerformingTakeDown = false;
public:
    UFUNCTION(BlueprintPure)
    float GetSpeed() const;

private:
    float Speed;
};
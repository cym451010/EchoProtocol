#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GuardCharacter.generated.h"

UCLASS()
class ECHOPROTOCOL_API AGuardCharacter : public ABaseCharacter
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
    virtual void HandleDeath() override;

public:
    // AI / Patrol
    AActor* GetCurrentPatrol() const;

    UPROPERTY(EditAnywhere, Category = "AI")
    TArray<AActor*> PatrolPoints;

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
    int32 GetCurrentPatrolIndex() const;

    void AdvancePatrolIndex();

private:
    float Speed;
    int32 CurrentPatrolIndex;
};
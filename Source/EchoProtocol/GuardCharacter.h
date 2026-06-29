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

    AActor* GetCurrentPatrol() const;

    UPROPERTY(EditInstanceOnly, Category = "AI")
    TArray<AActor*> PatrolPoints;

    UPROPERTY()
    class AEchoPlayerCharacter* Player;
private:
    // Animation
    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* DownMontage;
    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* ShootMontage;
    

    //Widget
    UPROPERTY(VisibleAnywhere, Category = "UI")
    class UWidgetComponent* TakeDownWidgetComponent;
    UPROPERTY(VisibleAnywhere, Category = "UI")
    class UWidgetComponent* GaugeWidgetComponent;

    UPROPERTY()
    class UGuardGaugeWidget* GuardGaugeWidget;

    bool bIsPerformingTakeDown = false;
public:
    UFUNCTION(BlueprintPure)
    float GetSpeed() const;
    UFUNCTION(BlueprintPure)
    float GetSightGauge() const;

    int32 GetCurrentPatrolIndex() const;
    void SetTakeDownWidget(bool bIsVisible);
    void PullTrigger();
    void AdvancePatrolIndex();
    void UpdateSightGauge(float DeltaTime);

private:
    float Speed;
    int32 CurrentPatrolIndex;
    float MaxSightGauge = 30.f;
    float SightGauge = 0.f;

};
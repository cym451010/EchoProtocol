// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GuardAIController.generated.h"

/**
 * 
 */
UCLASS()
class ECHOPROTOCOL_API AGuardAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AGuardAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere)
	class UBlackboardComponent* BlackboardComponent;
public:
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus);
	UPROPERTY(VisibleAnywhere, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> AIPerception;;
	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;

	bool GetCanSeePlayer() const;
private:
	struct FTimerHandle LoseSightTimerHandle;


	bool bCanSeePlayer = false;
};

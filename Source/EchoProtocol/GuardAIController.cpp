// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardAIController.h"

// Called when the game starts or when spawned
void AGuardAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!BehaviorTree)
	{
		UE_LOG(LogTemp, Warning, TEXT("BehaviorTree NullPtr"));
		return;
	}
	RunBehaviorTree(BehaviorTree);
}
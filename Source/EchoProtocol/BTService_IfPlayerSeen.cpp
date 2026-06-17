// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IfPlayerSeen.h"

#include "GuardAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_IfPlayerSeen::UBTService_IfPlayerSeen()
{
	NodeName = TEXT("If Player Seen?");
}

void UBTService_IfPlayerSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("BlackboardComponent Null"));
		return;
	}

	AGuardAIController* GuardAiController = Cast<AGuardAIController>(OwnerComp.GetAIOwner());
	if (!GuardAiController)
	{
		UE_LOG(LogTemp, Error, TEXT("GuardAiController Null"));
		return;
	}

	if (GuardAiController->GetCanSeePlayer())
	{
		BlackboardComponent->SetValueAsBool(TEXT("bCanSeePlayer"), true);
	}
	else
	{
		BlackboardComponent->ClearValue(TEXT("bCanSeePlayer"));
	}
}

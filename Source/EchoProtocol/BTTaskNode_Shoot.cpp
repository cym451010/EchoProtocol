// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"

#include "AIController.h"
#include "GuardCharacter.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}
	AGuardCharacter* Guard = Cast<AGuardCharacter>(AIController->GetPawn());
	if (!Guard)
	{
		return EBTNodeResult::Failed;
	}

	Guard->PullTrigger();
	return EBTNodeResult::Succeeded;
}

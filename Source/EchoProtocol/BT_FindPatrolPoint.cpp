// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_FindPatrolPoint.h"

#include "AIController.h"
#include "GuardCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBT_FindPatrolPoint::UBT_FindPatrolPoint()
{
	NodeName = TEXT("Find Patrol Point");
}

EBTNodeResult::Type UBT_FindPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AGuardCharacter* GuardCharacter = Cast<AGuardCharacter>(AIController->GetPawn());
	if (!GuardCharacter)
	{
		return EBTNodeResult::Failed;
	}


	AActor* PatrolPoint = GuardCharacter->GetCurrentPatrol();
	if (!PatrolPoint)
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector("PatrolPointsVector", PatrolPoint->GetActorLocation());

	if (GuardCharacter->CurrentPatrolIndex > 2)
	{
		return EBTNodeResult::Failed;
	}

	GuardCharacter->CurrentPatrolIndex++;

	if (GuardCharacter->CurrentPatrolIndex >= 3)
	{
		GuardCharacter->CurrentPatrolIndex = 0;
	}
	return EBTNodeResult::Succeeded;

	// TODO : 코드 리팩토링하기
}

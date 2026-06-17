// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	BlackboardComponent->ClearValue(BlackboardKey.GetSelectedKeyID());
	return EBTNodeResult::Succeeded;
}

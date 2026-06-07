// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BT_FindPatrolPoint.generated.h"

UCLASS()
class ECHOPROTOCOL_API UBT_FindPatrolPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UBT_FindPatrolPoint();
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Display, TEXT("Shoot"));

	return EBTNodeResult::Succeeded;
}

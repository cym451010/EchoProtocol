// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_IfPlayerSeen.generated.h"

/**
 * 
 */
UCLASS()
class ECHOPROTOCOL_API UBTService_IfPlayerSeen : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_IfPlayerSeen();

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

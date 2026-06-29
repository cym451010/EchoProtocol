// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GuardGaugeWidget.generated.h"

/**
 * 
 */
UCLASS()
class ECHOPROTOCOL_API UGuardGaugeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetSightGauge(float Value);
protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* SightProgressBar;
};

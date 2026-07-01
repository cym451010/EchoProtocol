// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WinGame.generated.h"

/**
 * 
 */
UCLASS()
class ECHOPROTOCOL_API UWinGame : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;

	UFUNCTION()
	void OnClickedRestartButton();
};

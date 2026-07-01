// Fill out your copyright notice in the Description page of Project Settings.


#include "WinGame.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UWinGame::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UWinGame::OnClickedRestartButton);
	}
}

void UWinGame::OnClickedRestartButton()
{
	UGameplayStatics::OpenLevel(this, TEXT("Lvl_ThirdPerson"));
}
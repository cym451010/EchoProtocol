// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOver::NativeConstruct()
{
    Super::NativeConstruct();

    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UGameOver::OnClickedRestartButton);
    }
}

void UGameOver::OnClickedRestartButton()
{
    UGameplayStatics::OpenLevel(this, TEXT("Lvl_ThirdPerson"));
}

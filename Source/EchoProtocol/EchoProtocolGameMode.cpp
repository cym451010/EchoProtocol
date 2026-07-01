// Copyright Epic Games, Inc. All Rights Reserved.

#include "EchoProtocolGameMode.h"

#include "EngineUtils.h"
#include "GuardCharacter.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

//TODO : 적 인원 실시간 확인 코드 짜기

AEchoProtocolGameMode::AEchoProtocolGameMode()
{
    PrimaryActorTick.bCanEverTick = true;

	// stub
    EnemyCnt = 0;
}

void AEchoProtocolGameMode::BeginPlay()
{
    Super::BeginPlay();

    for (TActorIterator<AGuardCharacter> Iterator(GetWorld()); Iterator; ++Iterator)
    {
        EnemyCnt++;
    }
}

void AEchoProtocolGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    WinGame();
}

void AEchoProtocolGameMode::WinGame()
{
    if (EnemyCnt > 0)
    {
        return;
    }

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (!PlayerController)
    {
        return;
    }

    if (!WinGameWidgetClass)
    {
        return;
    }

    WinGameWidget = CreateWidget<UUserWidget>(PlayerController, WinGameWidgetClass);
    WinGameWidget->AddToViewport();

    SetUpScreen();
}

void AEchoProtocolGameMode::GameOver()
{
    if (!GameOverWidgetClass)
    {
        UE_LOG(LogTemp, Error, TEXT("GameOverWidgetClass Nullptr"));
        return;
    }

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (!PlayerController)
    {
        return;
    }

    for (TActorIterator<AGuardCharacter> It(GetWorld()); It; ++It)
    {
        AGuardCharacter* Guard = *It;
        if (UWidgetComponent* WidgetComp = Guard->FindComponentByClass<UWidgetComponent>())
        {
            WidgetComp->SetVisibility(false);
        }
    }

    GameOverWidget = CreateWidget<UUserWidget>(PlayerController, GameOverWidgetClass);
    GameOverWidget->AddToViewport(100);

    SetUpScreen();
}

void AEchoProtocolGameMode::MinusEnemyCnt()
{
    if (EnemyCnt <= 0)
    {
        return;
    }

    EnemyCnt--;
}

void AEchoProtocolGameMode::SetUpScreen()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (!PlayerController)
    {
        return;
    }

    PlayerController->SetInputMode(FInputModeUIOnly());
    PlayerController->bShowMouseCursor = true;
    UGameplayStatics::SetGamePaused(this, true);
}

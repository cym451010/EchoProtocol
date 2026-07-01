// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EchoProtocolGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class AEchoProtocolGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	AEchoProtocolGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void WinGame();
	void GameOver();
	void SetUpScreen();
	void MinusEnemyCnt();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> GameOverWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinGameWidgetClass;
	UPROPERTY()
	class UUserWidget* GameOverWidget;
	UPROPERTY()
	class UUserWidget* WinGameWidget;

private:
	int32 EnemyCnt;
};




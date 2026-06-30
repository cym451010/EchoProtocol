// Copyright Epic Games, Inc. All Rights Reserved.

#include "EchoProtocolGameMode.h"

#include "Kismet/GameplayStatics.h"

AEchoProtocolGameMode::AEchoProtocolGameMode()
{
	// stub
}

void AEchoProtocolGameMode::GameOver()
{
	UE_LOG(LogTemp, Error, TEXT("게임 오버"));

	UGameplayStatics::SetGamePaused(this, true);
}

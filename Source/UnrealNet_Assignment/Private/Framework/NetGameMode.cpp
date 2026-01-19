// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetGameMode.h"
#include "Framework/NetGameState.h"

ANetGameMode::ANetGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	RoundTime = 60.0f;
}

void ANetGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 CurrentPlayerCount = GetNumPlayers();

	if (CurrentPlayerCount >= 2)
	{
		//if (!GetWorld()->GetTimerManager().IsTimerActive(WaitingTimerHandle))
		//{
		//	GetWorld()->GetTimerManager().SetTimer(
		//			WaitingTimerHandle,
		//			this,
		//			&ANetGameMode::StartRound,
		//			5.0f,
		//			false
		//		);
		//}
		StartRound();
	}
}

void ANetGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsGameStarted)
	{
		return;
	}

	RoundTime = FMath::Max(0.0f, RoundTime - DeltaTime);
	//UE_LOG(LogTemp,Log,TEXT("RoundTime : %f"), RoundTime);
	if (ANetGameState* MyGameState = GetGameState<ANetGameState>())
	{
		MyGameState->SetGameRemainingTime(RoundTime);
	}

	if (RoundTime <= 0)
	{
		FinishRound();
	}
}

void ANetGameMode::StartRound()
{
	bIsGameStarted = true;
}

void ANetGameMode::FinishRound()
{
}

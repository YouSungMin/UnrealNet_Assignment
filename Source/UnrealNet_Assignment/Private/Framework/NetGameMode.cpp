// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetGameMode.h"
#include "Framework/NetGameState.h"

ANetGameMode::ANetGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	RoundTime = 60.0f;
}

void ANetGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RoundTime = FMath::Max(0.0f, RoundTime - DeltaTime);

	if (ANetGameState* MyGameState = GetGameState<ANetGameState>())
	{
		MyGameState->SetGameRemainingTime(RoundTime);
	}

	if (RoundTime <= 0)
	{
		FinishRound();
	}
}

void ANetGameMode::FinishRound()
{
}

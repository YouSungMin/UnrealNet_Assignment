// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetPlayerState.h"
#include "Net/UnrealNetwork.h"

void ANetPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetPlayerState, GameScore);
}

void ANetPlayerState::AddScore(int32 Amount)
{
	if (HasAuthority())
	{
		GameScore += Amount;

		OnRep_GameScore();

		UE_LOG(LogTemp, Log, TEXT("Player %s Score Updated: %d"), *GetName(), GameScore);
	}
}

void ANetPlayerState::OnRep_GameScore()
{
	if (OnScoreChanged.IsBound())
	{
		OnScoreChanged.Broadcast(GameScore);
	}
}

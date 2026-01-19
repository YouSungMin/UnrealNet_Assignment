// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetGameState.h"
#include "Net/UnrealNetwork.h"

void ANetGameState::SetGameRemainingTime(float NewTime)
{
	if (HasAuthority())
	{
		GameRemainingTime = NewTime;
		//UE_LOG(LogTemp, Log, TEXT("GameRemainingTime : %f"), GameRemainingTime);
		OnRep_RemainingTime();
	}
}

void ANetGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANetGameState, GameRemainingTime);
}

void ANetGameState::OnRep_RemainingTime()
{
	if (OnTimeUpdated.IsBound())
	{
		//UE_LOG(LogTemp, Log, TEXT("OnTimeUpdated Broadcast"));
		OnTimeUpdated.Broadcast(GameRemainingTime);
	}
}

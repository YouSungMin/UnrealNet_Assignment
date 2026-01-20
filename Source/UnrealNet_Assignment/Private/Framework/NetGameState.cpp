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
	DOREPLIFETIME(ANetGameState, WinnerName);
}

void ANetGameState::SetWinner(FString NewWinnerName)
{
	if (HasAuthority())
	{
		WinnerName = NewWinnerName;
		OnRep_WinnerName();
	}
}

void ANetGameState::OnRep_RemainingTime()
{
	if (OnTimeUpdated.IsBound())
	{
		//UE_LOG(LogTemp, Log, TEXT("OnTimeUpdated Broadcast"));
		OnTimeUpdated.Broadcast(GameRemainingTime);
	}
}

void ANetGameState::OnRep_WinnerName()
{
	if (!WinnerName.IsEmpty())
	{
		//UE_LOG(LogTemp, Log, TEXT("OnGameEnded Broadcast"));
		OnGameEnded.Broadcast(WinnerName);
	}
}

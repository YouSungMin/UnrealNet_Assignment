// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetGameState.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

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
	DOREPLIFETIME(ANetGameState, StartCountdownTime);
	DOREPLIFETIME(ANetGameState, GameRemainingTime);
	DOREPLIFETIME(ANetGameState, bIsGameActive);
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

void ANetGameState::SetGameActive(bool bActive)
{
	if (HasAuthority())
	{
		bIsGameActive = bActive;
		OnRep_IsGameActive();
	}
}

void ANetGameState::UpdateStartCountdown(int32 NewTime)
{
	if (HasAuthority())
	{
		StartCountdownTime = NewTime;
		OnRep_StartCountdownTime();
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

void ANetGameState::OnRep_IsGameActive()
{
	if (OnGameActiveChanged.IsBound())
	{
		OnGameActiveChanged.Broadcast(bIsGameActive);
	}
}

void ANetGameState::OnRep_StartCountdownTime()
{
	if (OnStartCountdownUpdated.IsBound())
	{
		OnStartCountdownUpdated.Broadcast(StartCountdownTime);
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

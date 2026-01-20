// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NetGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeUpdated, float, NewTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameEnded, FString, WinnerName);
/**
 * 
 */
UCLASS()
class UNREALNET_ASSIGNMENT_API ANetGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	void SetGameRemainingTime(float NewTime);

	inline float GetGameRemainingTime() const { return GameRemainingTime;}

	void SetWinner(FString NewWinnerName);

	UFUNCTION()
	void OnRep_RemainingTime(); 

	UFUNCTION()
	void OnRep_WinnerName();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTimeUpdated OnTimeUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnGameEnded OnGameEnded;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_RemainingTime, BlueprintReadOnly, Category = "Game Data")
	float GameRemainingTime = 0.0f;

	UPROPERTY(ReplicatedUsing = OnRep_WinnerName)
		FString WinnerName = TEXT("");

};

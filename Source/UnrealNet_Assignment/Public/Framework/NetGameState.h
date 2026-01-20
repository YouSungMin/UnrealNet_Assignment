// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NetGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeUpdated, float, NewTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameEnded, FString, WinnerName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartCountdownUpdated, int32, NewCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameActiveChanged, bool, bIsActive);
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

	void SetGameActive(bool bActive);

	void UpdateStartCountdown(int32 NewTime);

	inline int32 GetStartCountdownTime() const {return StartCountdownTime;}

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_RemainingTime(); 

	UFUNCTION()
	void OnRep_WinnerName();

	UFUNCTION()
	void OnRep_IsGameActive();

	UFUNCTION()
	void OnRep_StartCountdownTime();

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTimeUpdated OnTimeUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnGameEnded OnGameEnded;

	UPROPERTY(BlueprintAssignable)
	FOnStartCountdownUpdated OnStartCountdownUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnGameActiveChanged OnGameActiveChanged;
protected:
	UPROPERTY(ReplicatedUsing = OnRep_RemainingTime, BlueprintReadOnly, Category = "Game Data")
	float GameRemainingTime = 0.0f;

	UPROPERTY(ReplicatedUsing = OnRep_WinnerName)
	FString WinnerName = TEXT("");

	UPROPERTY(ReplicatedUsing = OnRep_StartCountdownTime)
	int32 StartCountdownTime = -1;

	UPROPERTY(ReplicatedUsing = OnRep_IsGameActive)
	bool bIsGameActive = false;
};

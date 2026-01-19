// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NetGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeUpdated, float, NewTime);
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

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTimeUpdated OnTimeUpdated;
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_RemainingTime, BlueprintReadOnly, Category = "Game Data")
	float GameRemainingTime = 0.0f;

	UFUNCTION()
	void OnRep_RemainingTime();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALNET_ASSIGNMENT_API ANetGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ANetGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
protected:
	virtual void Tick(float DeltaTime)override;

	void StartRound();
	void FinishRound(); 

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RoundTime")
	float RoundTime;
	
	bool bIsGameStarted = false;

	FTimerHandle WaitingTimerHandle;
};

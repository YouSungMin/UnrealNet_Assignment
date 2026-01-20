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

	virtual AActor* ChoosePlayerStart(AController* Player) override;
protected:
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime)override;

	void StartRound();
	void FinishRound(); 
	void HandleStartingCountdown();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RoundTime")
	float RoundTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WaitingTime")
	int32 WaitingTime = 5;
	
	UPROPERTY()
	TObjectPtr<class ANetGameState> NetGameState;

	bool bIsGameStarted = false;

	FTimerHandle WaitingTimerHandle;
};

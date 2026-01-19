// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NetPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32, NewScore);
/**
 * 
 */
UCLASS()
class UNREALNET_ASSIGNMENT_API ANetPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetGameScore() const {return GameScore;}

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnScoreChanged OnScoreChanged;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void OnRep_GameScore();

protected:
	UPROPERTY(ReplicatedUsing = OnRep_GameScore, BlueprintReadOnly, Category = "Score")
	int32 GameScore = 0;
};

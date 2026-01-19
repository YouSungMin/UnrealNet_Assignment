// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUDWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class UNREALNET_ASSIGNMENT_API UInGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void UpdateRemainingTimeText(float NewTime);

	UFUNCTION()
	void UpdateMyScoreText();

	UFUNCTION()
	void UpdateOpponentScoreText();

protected:
	virtual void NativeConstruct()override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> RemainingTimeText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MyScoreText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> OpponentScoreText;
};

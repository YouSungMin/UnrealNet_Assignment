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
	void UpdateMyScoreText(int32 NewScore);

	UFUNCTION()
	void UpdateOpponentScoreText(int32 NewScore);

	void BindPlayerStates();
protected:
	virtual void NativeConstruct()override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> RemainingTimeText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MyScoreText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> OpponentScoreText;

private:
	bool bIsPlayerStatsBound = false;
};

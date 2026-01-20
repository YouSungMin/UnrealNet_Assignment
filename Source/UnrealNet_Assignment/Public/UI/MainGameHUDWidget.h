// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainGameHUDWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class UNREALNET_ASSIGNMENT_API UMainGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct()override;

	UFUNCTION()
	void OnCreateButtonClicked();

	UFUNCTION()
	void OnJoinButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CreateButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> JoinButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> InputIPAddress = nullptr;
private:
	TObjectPtr<class UNetGameInstance> GameInstance = nullptr;
};

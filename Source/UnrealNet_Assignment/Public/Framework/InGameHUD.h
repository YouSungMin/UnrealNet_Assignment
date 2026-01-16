// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALNET_ASSIGNMENT_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	inline TWeakObjectPtr<UUserWidget> GetHudWidget() const { return HudWidget; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HudWidgetClass = nullptr;

private:
	UPROPERTY()
	TWeakObjectPtr<UUserWidget> HudWidget = nullptr;
};

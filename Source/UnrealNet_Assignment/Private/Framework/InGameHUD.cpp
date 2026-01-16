// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/InGameHUD.h"
#include "Blueprint/UserWidget.h"

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();
	if (HudWidgetClass)
	{
		HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
		if (HudWidget.IsValid())
		{
			HudWidget->AddToViewport();
		}
	}
}

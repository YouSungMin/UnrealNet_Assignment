// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUDWidget.h"
#include "Components/TextBlock.h"
#include "Framework/NetGameState.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void UInGameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

    if (ANetGameState* NetGameState = Cast<ANetGameState>(GetWorld()->GetGameState()))
    {
        UpdateRemainingTimeText(NetGameState->GetGameRemainingTime());

        NetGameState->OnTimeUpdated.AddDynamic(this, &UInGameHUDWidget::UpdateRemainingTimeText);
    }
}

void UInGameHUDWidget::UpdateRemainingTimeText(float NewTime)
{
    UE_LOG(LogTemp, Log, TEXT("RemainingTimeText : %f"), NewTime);
    if (RemainingTimeText)
    {
        int32 Seconds = FMath::FloorToInt(NewTime);
        int32 MilliSeconds = FMath::FloorToInt((NewTime - Seconds) * 100);

        FString TimeString = FString::Printf(TEXT("%02d:%02d"), Seconds, MilliSeconds);

        RemainingTimeText->SetText(FText::FromString(TimeString));
    }
}

void UInGameHUDWidget::UpdateMyScoreText()
{
}

void UInGameHUDWidget::UpdateOpponentScoreText()
{
}


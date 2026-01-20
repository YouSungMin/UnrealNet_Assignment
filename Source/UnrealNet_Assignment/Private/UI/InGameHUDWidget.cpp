// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUDWidget.h"
#include "Components/TextBlock.h"
#include "Framework/NetGameState.h"
#include "Framework/NetPlayerState.h"
#include "Kismet/GameplayStatics.h"

void UInGameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

    if(ANetGameState* NetGameState = Cast<ANetGameState>(GetWorld()->GetGameState()))
    {
        UpdateRemainingTimeText(NetGameState->GetGameRemainingTime());

        NetGameState->OnStartCountdownUpdated.AddDynamic(this, &UInGameHUDWidget::UpdateInfoText);
        NetGameState->OnTimeUpdated.RemoveDynamic(this, &UInGameHUDWidget::UpdateRemainingTimeText);
        NetGameState->OnTimeUpdated.AddDynamic(this, &UInGameHUDWidget::UpdateRemainingTimeText);
        NetGameState->OnGameEnded.AddDynamic(this, &UInGameHUDWidget::ShowGameResult);

        UpdateInfoText(NetGameState->GetStartCountdownTime());
    }
    bIsPlayerStatsBound = false;
}

void UInGameHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (!bIsPlayerStatsBound)
    {
        BindPlayerStates();
    }
}

void UInGameHUDWidget::ShowGameResult(FString WinnerName)
{
    FString MyName = TEXT("");
    if (APlayerState* MyPS = GetOwningPlayerState())
    {
        MyName = MyPS->GetPlayerName();
    }

    FString ResultTextStr = TEXT("");
    FColor ResultColor = FColor::White;

    if (WinnerName == TEXT("Draw"))
    {
        ResultTextStr = TEXT("DRAW");
        ResultColor = FColor::Yellow;
    }
    else if (WinnerName == MyName)
    {
        ResultTextStr = TEXT("VICTORY!");
        ResultColor = FColor::Green;
    }
    else
    {
        ResultTextStr = TEXT("DEFEAT");
        ResultColor = FColor::Red;
    }

    if (ResultText)
    {
        ResultText->SetText(FText::FromString(ResultTextStr));
        ResultText->SetColorAndOpacity(ResultColor);
        ResultText->SetVisibility(ESlateVisibility::Visible);
    }
}

void UInGameHUDWidget::UpdateRemainingTimeText(float NewTime)
{
    //UE_LOG(LogTemp, Log, TEXT("RemainingTimeText : %f"), NewTime);
    if (RemainingTimeText)
    {
        int32 Seconds = FMath::FloorToInt(NewTime);
        int32 MilliSeconds = FMath::FloorToInt((NewTime - Seconds) * 100);

        FString TimeString = FString::Printf(TEXT("%02d:%02d"), Seconds, MilliSeconds);

        RemainingTimeText->SetText(FText::FromString(TimeString));
    }
}

void UInGameHUDWidget::UpdateMyScoreText(int32 NewScore)
{
    if (MyScoreText)
    {
        MyScoreText->SetText(FText::AsNumber(NewScore));
    }
}

void UInGameHUDWidget::UpdateOpponentScoreText(int32 NewScore)
{
    if (OpponentScoreText)
    {
        OpponentScoreText->SetText(FText::AsNumber(NewScore));
    }
}

void UInGameHUDWidget::UpdateInfoText(int32 NewCount)
{
    if (!ResultText) return;

    if (NewCount < 0)
    {
        ResultText->SetText(FText::FromString(TEXT("다른 플레이어를 기다리는 중...")));
        ResultText->SetColorAndOpacity(FLinearColor::White);
        ResultText->SetVisibility(ESlateVisibility::Visible);
    }
    else if (NewCount > 0)
    {
        FString CountStr = FString::Printf(TEXT("%d"), NewCount);
        ResultText->SetText(FText::FromString(CountStr));
        ResultText->SetColorAndOpacity(FLinearColor::Yellow);
        ResultText->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        ResultText->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UInGameHUDWidget::BindPlayerStates()
{
    ANetGameState* GameState = Cast<ANetGameState>(GetWorld()->GetGameState());

    if (!GameState) return;

    APlayerState* MyPS = GetOwningPlayerState();
    if (!MyPS) return;

    for (APlayerState* PS : GameState->PlayerArray)
    {
        ANetPlayerState* NetPS = Cast<ANetPlayerState>(PS);
        if (!NetPS) continue;

        if (PS == MyPS)
        {
            NetPS->OnScoreChanged.RemoveDynamic(this, &UInGameHUDWidget::UpdateMyScoreText);
            NetPS->OnScoreChanged.AddDynamic(this, &UInGameHUDWidget::UpdateMyScoreText);

            UpdateMyScoreText(NetPS->GetGameScore());
        }
        else
        {
            NetPS->OnScoreChanged.RemoveDynamic(this, &UInGameHUDWidget::UpdateOpponentScoreText);
            NetPS->OnScoreChanged.AddDynamic(this, &UInGameHUDWidget::UpdateOpponentScoreText);

            UpdateOpponentScoreText(NetPS->GetGameScore());
        }
    }
    if (GameState->PlayerArray.Num() >= 2)
    {
        bIsPlayerStatsBound = true;
        UE_LOG(LogTemp, Warning, TEXT("UI: 플레이어 2명 바인딩 완료. Tick 루프 종료."));
    }
}


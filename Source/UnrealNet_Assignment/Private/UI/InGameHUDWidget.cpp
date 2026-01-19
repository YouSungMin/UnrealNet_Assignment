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

        NetGameState->OnTimeUpdated.RemoveDynamic(this, &UInGameHUDWidget::UpdateRemainingTimeText);
        NetGameState->OnTimeUpdated.AddDynamic(this, &UInGameHUDWidget::UpdateRemainingTimeText);
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
        bIsPlayerStatsBound = true; // 이제 2명 다 왔으니 검사 끝!
        UE_LOG(LogTemp, Warning, TEXT("UI: 플레이어 2명 바인딩 완료. Tick 루프 종료."));
    }
}


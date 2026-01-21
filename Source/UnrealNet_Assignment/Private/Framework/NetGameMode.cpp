// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetGameMode.h"
#include "Framework/NetGameState.h"
#include "Framework/NetPlayerState.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"

ANetGameMode::ANetGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	RoundTime = 60.0f;
}

void ANetGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerSpawn(NewPlayer);
	int32 CurrentPlayerCount = GetNumPlayers();

	if (CurrentPlayerCount < 2)
	{
		if (NetGameState)
		{
			NetGameState->UpdateStartCountdown(-1);
		}
	}
	else if (CurrentPlayerCount >= 2)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(WaitingTimerHandle))
		{
			GetWorld()->GetTimerManager().SetTimer(
				WaitingTimerHandle,
				this,
				&ANetGameMode::HandleStartingCountdown,
				1.0f,
				true
			);
		}
	}
}

void ANetGameMode::BeginPlay()
{
	Super::BeginPlay();

	NetGameState = GetGameState<ANetGameState>();
	if (NetGameState)
	{
		NetGameState->SetGameRemainingTime(RoundTime);
	}
}

void ANetGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsGameStarted)
	{
		return;
	}

	RoundTime = FMath::Max(0.0f, RoundTime - DeltaTime);
	//UE_LOG(LogTemp,Log,TEXT("RoundTime : %f"), RoundTime);
	if (NetGameState)
	{
		NetGameState->SetGameRemainingTime(RoundTime);
	}

	if (RoundTime <= 0)
	{
		FinishRound();
	}
}

void ANetGameMode::StartRound()
{
	bIsGameStarted = true;

	if (NetGameState)
	{
		NetGameState->SetGameActive(true);
	}
}

void ANetGameMode::FinishRound()
{
	if(!bIsGameStarted) return;
	bIsGameStarted = false;

	if (!NetGameState) return;

	int32 P1Score = -1;
	int32 P2Score = -1;
	FString P1Name = TEXT("");
	FString P2Name = TEXT("");

	if (NetGameState->PlayerArray.Num() >= 2)
	{
		ANetPlayerState* PS1 = Cast<ANetPlayerState>(NetGameState->PlayerArray[0]);
		if (PS1) { P1Score = PS1->GetGameScore(); P1Name = PS1->GetPlayerName(); }

		ANetPlayerState* PS2 = Cast<ANetPlayerState>(NetGameState->PlayerArray[1]);
		if (PS2) { P2Score = PS2->GetGameScore(); P2Name = PS2->GetPlayerName(); }
	}

	FString FinalWinner = TEXT("Draw");

	if (P1Score > P2Score)
	{
		FinalWinner = P1Name;
	}
	else if (P2Score > P1Score)
	{
		FinalWinner = P2Name;
	}
	else
	{
		FinalWinner = TEXT("Draw");
	}

	UE_LOG(LogTemp, Warning, TEXT("게임 종료 승자: %s"), *FinalWinner);
	NetGameState->SetGameActive(false);
	NetGameState->SetWinner(FinalWinner);
}

void ANetGameMode::HandleStartingCountdown()
{
	if (!NetGameState) return;

	NetGameState->UpdateStartCountdown(WaitingTime);

	if (WaitingTime <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(WaitingTimerHandle);
		StartRound();
	}
	else
	{
		WaitingTime--;
	}
}

void ANetGameMode::PlayerSpawn(APlayerController* NewPlayer)
{
	int32 PlayerIndex = GetNumPlayers() - 1;

	FString TargetTag = FString::Printf(TEXT("Spawn_%d"), PlayerIndex);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (APlayerStart* TargetStart = Cast<APlayerStart>(Actor))
		{
			if (TargetStart->PlayerStartTag == FName(*TargetTag))
			{
				if (APawn* MyPawn = NewPlayer->GetPawn())
				{
					MyPawn->SetActorLocationAndRotation(
						TargetStart->GetActorLocation(),
						TargetStart->GetActorRotation()
					);

					UE_LOG(LogTemp, Warning, TEXT("플레이어 %d를 %s로 이동시켰습니다."), PlayerIndex, *TargetTag);
				}
				break;
			}
		}
	}
}

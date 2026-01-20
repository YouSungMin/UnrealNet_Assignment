// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainGameHUDWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/NetGameInstance.h"

void UMainGameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (CreateButton)
	{
		CreateButton->OnClicked.AddDynamic(this, &UMainGameHUDWidget::OnCreateButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UMainGameHUDWidget::OnJoinButtonClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainGameHUDWidget::OnExitButtonClicked);
	}

	GameInstance = Cast<UNetGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (APlayerController* PC = GetOwningPlayer())
	{
		PC->bShowMouseCursor = true;

		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(this->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PC->SetInputMode(InputMode);
	}
}

void UMainGameHUDWidget::OnCreateButtonClicked()
{
	if (GameInstance)
	{
		GameInstance->CreateServer();
	}
}

void UMainGameHUDWidget::OnJoinButtonClicked()
{
	if (GameInstance)
	{
		FString IPAddress = GameInstance->GetIPAddress();
		if (InputIPAddress)
		{
			FString InputIP = InputIPAddress->GetText().ToString();
			if (!InputIP.IsEmpty())
			{
				IPAddress = InputIP;
			}
		}

		GameInstance->JoinServer(IPAddress);
	}
}

void UMainGameHUDWidget::OnExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}

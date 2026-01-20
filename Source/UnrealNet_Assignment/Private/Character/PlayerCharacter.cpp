// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "Framework/NetGameState.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
    //SetPlayerMoveInput(false);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    InitPlayerInput();
}

void APlayerCharacter::OnRep_Controller()
{
    Super::OnRep_Controller();
    InitPlayerInput();
}

void APlayerCharacter::OnGameActiveChanged(bool bIsActive)
{
    SetPlayerMoveInput(bIsActive);
}

void APlayerCharacter::InitPlayerInput()
{
    if (ANetGameState* GS = Cast<ANetGameState>(GetWorld()->GetGameState()))
    {
        GS->OnGameActiveChanged.RemoveDynamic(this, &APlayerCharacter::OnGameActiveChanged);
        GS->OnGameActiveChanged.AddDynamic(this, &APlayerCharacter::OnGameActiveChanged);
    }
}

void APlayerCharacter::SetPlayerMoveInput(bool bEnable)
{
    FString RoleString = HasAuthority() ? TEXT("Server") : TEXT("Client");
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PC->SetIgnoreMoveInput(!bEnable);
        PC->SetIgnoreLookInput(!bEnable);

        UE_LOG(LogTemp, Error, TEXT("[%s] Input Enabled: %s"), *GetName(), !bEnable ? TEXT("True") : TEXT("False"));
    }
}
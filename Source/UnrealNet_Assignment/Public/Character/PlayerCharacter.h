// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"
class FInputActionValue;
UCLASS()
class UNREALNET_ASSIGNMENT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Controller() override;
	UFUNCTION()
	void OnGameActiveChanged(bool bIsActive);

private:
	void InitPlayerInput();
private:
	void SetPlayerMoveInput(bool bEnable);
};

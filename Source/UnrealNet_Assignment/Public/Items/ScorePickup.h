// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScorePickup.generated.h"

UCLASS()
class UNREALNET_ASSIGNMENT_API AScorePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScorePickup();

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComp = nullptr;

	// 2. 충돌 범위
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class USphereComponent> SphereComp = nullptr;

	UPROPERTY(EditAnywhere, Category = "Pickup Properties")
	int32 ScoreAmount = 1;
};

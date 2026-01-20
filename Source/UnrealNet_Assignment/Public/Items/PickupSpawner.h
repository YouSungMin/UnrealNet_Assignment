// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSpawner.generated.h"

UCLASS()
class UNREALNET_ASSIGNMENT_API APickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	void SpawnItem();

	UFUNCTION()
	void HandleGameActiveChanged(bool bIsActive);
protected:
	UPROPERTY()
	TWeakObjectPtr<class UNavigationSystemV1> NavSystem;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<class AActor> ItemClass;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnRadius = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnInterval = 3.0f;

	UPROPERTY(VisibleAnywhere, Category = "Spawner")
	TObjectPtr<class USphereComponent> SpawnRadiusComp;

	FTimerHandle SpawnTimerHandle;
};

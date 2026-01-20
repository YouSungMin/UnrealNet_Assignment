// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickupSpawner.h"
#include "Items/ScorePickup.h"
#include "NavigationSystem.h"
#include "Components/SphereComponent.h"
#include "Framework/NetGameState.h"

// Sets default values
APickupSpawner::APickupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpawnRadiusComp = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnRadiusComp"));
	RootComponent = SpawnRadiusComp;

	SpawnRadiusComp->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();

	NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (HasAuthority())
	{
		ANetGameState* GS = Cast<ANetGameState>(GetWorld()->GetGameState());
		if (GS)
		{
			GS->OnGameActiveChanged.AddDynamic(this, &APickupSpawner::HandleGameActiveChanged);
		}
	}
}

void APickupSpawner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (SpawnRadiusComp)
	{
		SpawnRadiusComp->SetSphereRadius(SpawnRadius);
	}
}

void APickupSpawner::SpawnItem()
{
	if (!ItemClass && !NavSystem.IsValid()) return;

	FNavLocation RandomLocation;

	bool bFound = NavSystem->GetRandomPointInNavigableRadius(
		GetActorLocation(),
		SpawnRadius,
		RandomLocation
	);

	if (bFound)
	{
		FVector SpawnPos = RandomLocation.Location + FVector(0, 0, 50.0f);
		FRotator SpawnRot = FRotator::ZeroRotator;

		GetWorld()->SpawnActor<AActor>(ItemClass, SpawnPos, SpawnRot);
	}
}

void APickupSpawner::HandleGameActiveChanged(bool bIsActive)
{
	if (!HasAuthority()) return;

	if (bIsActive)
	{
		GetWorld()->GetTimerManager().SetTimer(
			SpawnTimerHandle,
			this,
			&APickupSpawner::SpawnItem,
			SpawnInterval,
			true
		);
		SpawnItem();
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}
}


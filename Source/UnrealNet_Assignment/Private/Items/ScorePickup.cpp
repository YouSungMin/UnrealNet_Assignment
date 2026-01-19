// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ScorePickup.h"
#include "Components/SphereComponent.h"
#include "Framework/NetPlayerState.h"

// Sets default values
AScorePickup::AScorePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(SphereComp);
	SphereComp->SetSphereRadius(50.0f);
	SphereComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));


}

void AScorePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!HasAuthority())
	{
		return;
	}

	if (APawn* PlayerPawn = Cast<APawn>((OtherActor)))
	{
		if (ANetPlayerState* NetPS = PlayerPawn->GetPlayerState<ANetPlayerState>())
		{
			// 점수 추가 (서버에서 실행되므로 안전함)
			NetPS->AddScore(ScoreAmount);

			Destroy();
		}
	}
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NetGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALNET_ASSIGNMENT_API UNetGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UNetGameInstance();

	virtual void Init() override;
	UFUNCTION(BlueprintCallable, Category = "Network")
	void CreateServer();

	UFUNCTION(BlueprintCallable, Category = "Network")
	void JoinServer(FString IPAddress);

	UFUNCTION(BlueprintCallable, Category = "Network")
	void DisconnectServer();

	inline const FString& GetIPAddress() const { return ServerIP; }
private:
	UFUNCTION()
	void HandleNetworkFailure(
		UWorld* World, UNetDriver* NetDirever, ENetworkFailure::Type FailureType, const FString& ErrorString);

	UFUNCTION()
	void HandleTravelFailure(
		UWorld* World, ETravelFailure::Type FailureType, const FString& ErrorString);

protected:
	// 접속할 서버 IP
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NetGame")
	FString ServerIP = "127.0.0.1";

	// 게임 시작 시 로드할 맵
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NetGame")
	TSoftObjectPtr<UWorld> MainLevelAsset = nullptr;

	// 서버 생성 시 로드할 맵
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NetGame")
	TSoftObjectPtr<UWorld> ServerLevelAsset = nullptr;


	// 최대 접속가능한 플레이어 수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NetGame")
	int32 MaxPlayers = 2;
};

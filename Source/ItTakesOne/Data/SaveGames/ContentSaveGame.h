// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ContentSaveGame.generated.h"

USTRUCT()
struct FActorSaveData
{
	GENERATED_BODY()

public:
	FActorSaveData()
	{
		bDeferLoad = false;
		Class = nullptr;
	}

	UPROPERTY()
	FName Name;

	UPROPERTY()
	UClass* Class;

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	bool bDeferLoad;

	UPROPERTY()
	TArray<uint8> ByteData;
};

USTRUCT()
struct FPlayableWorldSaveData
{
	GENERATED_BODY()

public:
	FPlayableWorldSaveData()
	{
		bInitialized = false;
		bPlaythroughComplete = false;
	}

	UPROPERTY()
	bool bInitialized;

	UPROPERTY()
	bool bPlaythroughComplete;

	UPROPERTY()
	TArray<FActorSaveData> Actors;
};

UCLASS()
class ITTAKESONE_API UContentSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UContentSaveGame();

	UPROPERTY()
	FPlayableWorldSaveData TestWorld;

	UPROPERTY()
	FPlayableWorldSaveData Home;

	UPROPERTY()
	FPlayableWorldSaveData ClockLand;

	UPROPERTY()
	FPlayableWorldSaveData SkyLand;

	bool LoadActor(AActor* Actor, FActorSaveData& Data);
	bool SaveActor(AActor* Actor, FActorSaveData& Data);

	FActorSaveData* FindData(TArray<FActorSaveData>& ActorData, const AActor* Actor);
};

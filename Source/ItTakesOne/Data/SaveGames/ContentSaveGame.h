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
	UPROPERTY()
	FName ActorName;

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
	}

	UPROPERTY()
	bool bInitialized;

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
};

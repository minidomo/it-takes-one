// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ContentSaveGame.generated.h"

UCLASS()
class ITTAKESONE_API UContentSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UContentSaveGame();

	UPROPERTY()
	FString ActiveCheckpointLabel;
};

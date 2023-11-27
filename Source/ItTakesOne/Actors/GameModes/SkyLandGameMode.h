// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayableGameModeBase.h"
#include "SkyLandGameMode.generated.h"

UCLASS()
class ITTAKESONE_API ASkyLandGameMode : public APlayableGameModeBase
{
	GENERATED_BODY()

public:
	ASkyLandGameMode();

	virtual FPlayableWorldSaveData* GetPlayableWorldSaveData() override;
};

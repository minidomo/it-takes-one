// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayableGameModeBase.h"
#include "HomeGameMode.generated.h"

UCLASS()
class ITTAKESONE_API AHomeGameMode : public APlayableGameModeBase
{
	GENERATED_BODY()

public:
	AHomeGameMode();

	virtual FPlayableWorldSaveData* GetPlayableWorldSaveData() override;
};

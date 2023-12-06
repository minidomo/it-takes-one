// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayableGameModeBase.h"
#include "ClockLandGameMode.generated.h"

UCLASS()
class ITTAKESONE_API AClockLandGameMode : public APlayableGameModeBase
{
	GENERATED_BODY()

public:
	AClockLandGameMode();

protected:
	virtual void OnPlayerDied(ACharacter* Character, AController* Controller) override;
	
public:
	virtual FPlayableWorldSaveData* GetPlayableWorldSaveData() override;
};

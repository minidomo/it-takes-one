// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "MainWorldSettings.generated.h"

class APlayerStart;

UCLASS()
class ITTAKESONE_API AMainWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	AMainWorldSettings();

protected:
	UPROPERTY(EditInstanceOnly)
	APlayerStart* DefaultSpawnPoint;

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE APlayerStart* GetDefaultSpawnPoint() const { return DefaultSpawnPoint; }
};

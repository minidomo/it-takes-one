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
	UPROPERTY(EditInstanceOnly, Category = Variables)
	APlayerStart* DefaultSpawnPoint;

	UPROPERTY(EditInstanceOnly, Category = "Variables|Warnings")
	bool bDisableDefaultSpawnPointWarning;

	UPROPERTY(EditInstanceOnly, Category = "Variables|Debug")
	bool bShowCheckpointAreas;

public:
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	
	FORCEINLINE APlayerStart* GetDefaultSpawnPoint() const { return DefaultSpawnPoint; }
};

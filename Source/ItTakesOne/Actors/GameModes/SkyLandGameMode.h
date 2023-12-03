// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayableGameModeBase.h"
#include "SkyLandGameMode.generated.h"

class ACoreCrystal;
class AWindBossCharacter;
class ASkyPlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCoreCrystalDestroyedDelegate);

UCLASS()
class ITTAKESONE_API ASkyLandGameMode : public APlayableGameModeBase
{
	GENERATED_BODY()

public:
	ASkyLandGameMode();

protected:
	UPROPERTY()
	ASkyPlayerState* PlayerState;

	UPROPERTY()
	AWindBossCharacter* BossCharacter;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACoreCrystal> CoreCrystalClass;

public:
	UPROPERTY()
	FOnCoreCrystalDestroyedDelegate OnCoreCrystalDestroyedDelegate;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPlayerHealthUpdate(float OldHealth, float NewHealth);

	UFUNCTION()
	void OnBossHealthUpdate(float OldHealth, float NewHealth);

	UFUNCTION()
	void OnCoreCrystalDestroyed();

	void SpawnCoreCrystal();

public:
	virtual FPlayableWorldSaveData* GetPlayableWorldSaveData() override;
};

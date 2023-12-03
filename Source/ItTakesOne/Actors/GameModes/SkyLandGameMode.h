// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayableGameModeBase.h"
#include "SkyLandGameMode.generated.h"

class ALevelTransitionActor;
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
	AWindBossCharacter* BossCharacter;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACoreCrystal> CoreCrystalClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ALevelTransitionActor> LevelTransitionActorClass;

public:
	UPROPERTY()
	FOnCoreCrystalDestroyedDelegate OnCoreCrystalDestroyedDelegate;

protected:
	virtual void BeginPlay() override;
	virtual void OnPlayerDied(ACharacter* Character, AController* Controller) override;

	UFUNCTION()
	void OnBossDestroyed(AActor* DestroyedActor);

	UFUNCTION()
	void OnCoreCrystalDestroyed();

	void SpawnCoreCrystal();

public:
	virtual FPlayableWorldSaveData* GetPlayableWorldSaveData() override;
};

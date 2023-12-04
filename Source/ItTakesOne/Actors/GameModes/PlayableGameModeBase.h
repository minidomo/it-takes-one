// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ItTakesOne/Data/SaveGames/ContentSaveGame.h"
#include "PlayableGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerDiedDelegate, ACharacter*, Character, AController*, Controller);

UCLASS()
class ITTAKESONE_API APlayableGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APlayableGameModeBase();

public:
	UPROPERTY()
	FOnPlayerDiedDelegate OnPlayerDiedDelegate;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPlayerDied(ACharacter* Character, AController* Controller);

public:
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual void InitGameState() override;

	virtual FPlayableWorldSaveData* GetPlayableWorldSaveData();

	void LoadPlayerState(APlayerState* PlayerState);
	void LoadSaveGame();
	void WriteSaveGame();
};

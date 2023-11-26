// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PlayableGameStateBase.generated.h"

class APlayerStart;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActiveSpawnPointUpdateDelegate, APlayerStart*, OldSpawnPoint,
                                             APlayerStart*, NewSpawnPoint);

UCLASS()
class ITTAKESONE_API APlayableGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	APlayableGameStateBase();

protected:
	UPROPERTY()
	APlayerStart* ActiveSpawnPoint;

public:
	UPROPERTY()
	FOnActiveSpawnPointUpdateDelegate OnActiveSpawnPointUpdateDelegate;

public:
	virtual void PreInitializeComponents() override;

	bool UpdateActiveSpawnPoint(APlayerStart* NewActiveSpawnPoint);

	FORCEINLINE APlayerStart* GetActiveSpawnPoint() const { return ActiveSpawnPoint; }
};

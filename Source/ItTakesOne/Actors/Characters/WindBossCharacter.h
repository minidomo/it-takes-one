// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossCharacterBase.h"
#include "WindBossCharacter.generated.h"

class ARock;
class ARingWave;

UCLASS()
class ITTAKESONE_API AWindBossCharacter : public ABossCharacterBase
{
	GENERATED_BODY()

public:
	AWindBossCharacter();

protected:
	UPROPERTY(EditAnywhere, SaveGame)
	float Health;

	UPROPERTY(EditAnywhere, SaveGame)
	float MaxHealth;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ARingWave> RingWaveClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ARock> RockClass;

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	void RingWaveAttack();
	void RockThrowAttack();
	void WindBlastAndRockThrowAttack();
};

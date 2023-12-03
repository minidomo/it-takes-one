// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Logging/LogMacros.h"
#include "CoreMinimal.h"
#include "BossCharacterBase.h"
#include "ItTakesOne/Misc/Delegates.h"
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

	UPROPERTY(EditAnywhere, SaveGame)
	TSubclassOf<ARingWave> RingWaveClass;

	UPROPERTY(EditAnywhere, SaveGame)
	TSubclassOf<ARock> RockClass;

public:
	UPROPERTY()
	FOnHealthUpdateDelegate OnHealthUpdateDelegate;

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	void ApplyDamage(float Damage);

	void RingWaveAttack();
	void RockThrowAttack();
	void WindBlastAndRockThrowAttack();
};

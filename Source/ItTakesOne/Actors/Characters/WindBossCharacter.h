// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Logging/LogMacros.h"
#include "CoreMinimal.h"
#include "BossCharacterBase.h"
#include "ItTakesOne/Misc/Delegates.h"
#include "WindBossCharacter.generated.h"

class ARock;
class ARingWave;

UENUM(BlueprintType)
enum class EWindBossAttack : uint8
{
	None UMETA(Hidden),
	RingWave,
	RockThrow,
};

ENUM_CLASS_FLAGS(EWindBossAttack);

UCLASS()
class ITTAKESONE_API AWindBossCharacter : public ABossCharacterBase
{
	GENERATED_BODY()

public:
	AWindBossCharacter();

private:
	FTimerHandle AttackCompleteTimerHandle;
	FTimerHandle AttackStartTimerHandle;

protected:
	UPROPERTY(EditAnywhere, SaveGame)
	float Health;

	UPROPERTY(EditAnywhere, SaveGame)
	float MaxHealth;

	UPROPERTY(EditAnywhere, SaveGame)
	TSubclassOf<ARingWave> RingWaveClass;

	UPROPERTY(EditAnywhere, SaveGame)
	TSubclassOf<ARock> RockClass;

	UPROPERTY(EditAnywhere, SaveGame)
	uint32 ActorsPerRingWave;

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

	void RingWaveAttackSequence();
	void RockThrowAttackSequence();

	UFUNCTION()
	void DispatchAttackComplete();
};

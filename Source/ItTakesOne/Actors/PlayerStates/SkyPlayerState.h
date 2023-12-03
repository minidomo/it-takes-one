// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayablePlayerStateBase.h"
#include "ItTakesOne/Misc/Delegates.h"
#include "SkyPlayerState.generated.h"

UCLASS()
class ITTAKESONE_API ASkyPlayerState : public APlayablePlayerStateBase
{
	GENERATED_BODY()

public:
	ASkyPlayerState();

private:
	FTimerHandle UntilHealTimerHandle;

protected:
	UPROPERTY(EditAnywhere, SaveGame)
	float MaxHealth;

	UPROPERTY(EditAnywhere, SaveGame)
	float Health;

	UPROPERTY(EditAnywhere, SaveGame)
	float SecondsUntilHeal;

public:
	UPROPERTY()
	FOnHealthUpdateDelegate OnHealthUpdateDelegate;

public:
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	void ApplyDamage(float Damage);
	void Heal(float Delta);

	UFUNCTION()
	void StartHeal();
};

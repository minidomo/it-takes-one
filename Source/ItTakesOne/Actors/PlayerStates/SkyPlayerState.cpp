// Fill out your copyright notice in the Description page of Project Settings.

#include "SkyPlayerState.h"

ASkyPlayerState::ASkyPlayerState()
{
	MaxHealth = 100.f;
	Health = 100.f;
	SecondsUntilHeal = 7.f;
}

void ASkyPlayerState::ApplyDamage(float Damage)
{
	const float OldHealth = Health;
	Health = FMath::Clamp(Health - Damage, 0, MaxHealth);
	OnHealthUpdateDelegate.Broadcast(OldHealth, Health);

	if (Health > 0)
	{
		// only heal if player is actually alive
		GetWorldTimerManager().SetTimer(UntilHealTimerHandle, this, &ASkyPlayerState::StartHeal, SecondsUntilHeal);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(UntilHealTimerHandle);
	}
}

void ASkyPlayerState::StartHeal()
{
	Heal(MaxHealth);
}

void ASkyPlayerState::Heal(float Delta)
{
	const float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0, MaxHealth);
	OnHealthUpdateDelegate.Broadcast(OldHealth, Health);
}

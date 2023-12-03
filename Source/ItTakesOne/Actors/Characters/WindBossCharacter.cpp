// Fill out your copyright notice in the Description page of Project Settings.

#include "WindBossCharacter.h"

#include "Components/CapsuleComponent.h"
#include "ItTakesOne/Actors/Boss/Attacks/RingWave.h"
#include "ItTakesOne/Actors/Boss/Attacks/Rock.h"

AWindBossCharacter::AWindBossCharacter()
{
	BossName = "Wind Legend";
	Health = 400.f;
	MaxHealth = 400.f;
}

void AWindBossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWindBossCharacter::ApplyDamage(float Damage)
{
	const float OldHealth = Health;
	Health = FMath::Clamp(Health - Damage, 0, MaxHealth);
	OnHealthUpdateDelegate.Broadcast(OldHealth, Health);
}

void AWindBossCharacter::RingWaveAttack()
{
	const auto Location = GetActorLocation();
	GetWorld()->SpawnActor(RingWaveClass, &Location);
	OnAttackCompleteDelegate.Broadcast();
}

void AWindBossCharacter::RockThrowAttack()
{
	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
	const FVector Direction = (PlayerLocation - GetActorLocation()).GetSafeNormal();

	TArray<AActor*> Actors;
	constexpr uint32 MaxActors = 1;

	for (uint32 Index = 0; Index < MaxActors; ++Index)
	{
		const FVector Origin = GetActorLocation() + Direction * GetCapsuleComponent()->GetScaledCapsuleRadius();

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		const auto Rock = GetWorld()->SpawnActor<ARock>(RockClass, Origin, Direction.Rotation(), Params);
		if (IsValid(Rock))
		{
			Rock->SetDirection(Direction);
			Actors.Add(Rock);
		}
	}


	for (const auto& Actor : Actors)
	{
		Actor->SetActorTickEnabled(true);
	}

	OnAttackCompleteDelegate.Broadcast();
}

void AWindBossCharacter::WindBlastAndRockThrowAttack()
{
	OnAttackCompleteDelegate.Broadcast();
}

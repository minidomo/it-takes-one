// Fill out your copyright notice in the Description page of Project Settings.

#include "WindBossCharacter.h"

#include "Components/CapsuleComponent.h"
#include "ItTakesOne/Actors/Attacks/RingWave.h"
#include "ItTakesOne/Actors/Attacks/Rock.h"

AWindBossCharacter::AWindBossCharacter()
{
	BossName = "Wind Legend";
	Health = 500.f;
	MaxHealth = 500.f;
}

void AWindBossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWindBossCharacter::RingWaveAttack()
{
	const auto Location = GetActorLocation();
	GetWorld()->SpawnActor(RingWaveClass, &Location);
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
		const auto Rock = GetWorld()->SpawnActor<ARock>(RockClass, Origin, Direction.Rotation());
		Rock->SetSpeed(4000);

		Rock->SetDirection(Direction);
		Actors.Add(Rock);
	}


	for (const auto& Actor : Actors)
	{
		Actor->SetActorTickEnabled(true);
	}
}

void AWindBossCharacter::WindBlastAndRockThrowAttack()
{
}

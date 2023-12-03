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
	ActorsPerRingWave = 5;
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

	if (FMath::IsNearlyZero(Health))
	{
		Destroy();
	}
}

void AWindBossCharacter::RingWaveAttack()
{
	const auto PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
	if (!PlayerCharacter) { return; }

	const auto PlayerHeight = PlayerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2;
	const auto PlayerLocation = PlayerCharacter->GetActorLocation();
	const FVector Direction = (PlayerLocation - GetActorLocation()).GetSafeNormal();

	TArray<AActor*> Actors;
	const float DeltaZ = PlayerHeight;

	FVector Location = GetActorLocation();
	Location.Z -= DeltaZ * ActorsPerRingWave / 2;

	for (uint32 Index = 0; Index < ActorsPerRingWave; ++Index)
	{
		const FVector Origin = Location + Direction * GetCapsuleComponent()->GetScaledCapsuleRadius();

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		const auto RingWave = GetWorld()->SpawnActor<
			ARingWave>(RingWaveClass, Origin, Direction.Rotation(), Params);
		if (IsValid(RingWave))
		{
			RingWave->SetDirection(Direction);
			Actors.Add(RingWave);
		}

		Location.Z += FMath::RandRange(DeltaZ + PlayerHeight / 2, DeltaZ + PlayerHeight * 2);
	}

	for (const auto& Actor : Actors)
	{
		Actor->SetActorTickEnabled(true);
	}
}

void AWindBossCharacter::RockThrowAttack()
{
	const auto PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
	if (!PlayerCharacter) { return; }

	const auto PlayerLocation = PlayerCharacter->GetActorLocation();
	const FVector Direction = (PlayerLocation - GetActorLocation()).GetSafeNormal();

	TArray<AActor*> Actors;
	const FVector Origin = GetActorLocation() + Direction * GetCapsuleComponent()->GetScaledCapsuleRadius();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const auto Rock = GetWorld()->SpawnActor<ARock>(RockClass, Origin, Direction.Rotation(), Params);
	if (IsValid(Rock))
	{
		Rock->SetDirection(Direction);
		Actors.Add(Rock);
	}

	for (const auto& Actor : Actors)
	{
		Actor->SetActorTickEnabled(true);
	}
}

void AWindBossCharacter::RingWaveAttackSequence()
{
	GetWorldTimerManager().SetTimer(AttackStartTimerHandle, this, &AWindBossCharacter::RingWaveAttack, 1.f, true, 0);
	GetWorldTimerManager().SetTimer(AttackCompleteTimerHandle, this, &AWindBossCharacter::DispatchAttackComplete, 5.f);
}

void AWindBossCharacter::RockThrowAttackSequence()
{
	GetWorldTimerManager().SetTimer(AttackStartTimerHandle, this, &AWindBossCharacter::RockThrowAttack, .4f, true,
	                                0);
	GetWorldTimerManager().SetTimer(AttackCompleteTimerHandle, this, &AWindBossCharacter::DispatchAttackComplete, 3.f);
}

void AWindBossCharacter::DispatchAttackComplete()
{
	GetWorldTimerManager().ClearTimer(AttackStartTimerHandle);
	OnAttackCompleteDelegate.Broadcast();
}

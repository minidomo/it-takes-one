// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckpointBase.h"

#include "ItTakesOne/_Temp/TestGameState.h"

ACheckpointBase::ACheckpointBase()
{
}

void ACheckpointBase::BeginPlay()
{
	Super::BeginPlay();
	if (!SpawnPoint)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: spawn point is not set"), *GetActorNameOrLabel());
	}
}

void ACheckpointBase::Activate()
{
	if (const auto GameState = GetWorld()->GetGameState<ATestGameState>())
	{
		GameState->UpdateActiveSpawnPoint(SpawnPoint);
	}
}

bool ACheckpointBase::IsActive()
{
	if (const auto GameState = GetWorld()->GetGameState<ATestGameState>())
	{
		return SpawnPoint == GameState->GetActiveSpawnPoint();
	}

	return false;
}

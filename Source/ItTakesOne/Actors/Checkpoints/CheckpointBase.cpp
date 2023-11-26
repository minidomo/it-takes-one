// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckpointBase.h"

#include "ItTakesOne/Actors/GameStates/PlayableGameStateBase.h"

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
	if (const auto GameState = GetWorld()->GetGameState<APlayableGameStateBase>())
	{
		GameState->UpdateActiveSpawnPoint(SpawnPoint);
		Destroy();
	}
}

bool ACheckpointBase::IsActive()
{
	if (const auto GameState = GetWorld()->GetGameState<APlayableGameStateBase>())
	{
		return SpawnPoint == GameState->GetActiveSpawnPoint();
	}

	return false;
}

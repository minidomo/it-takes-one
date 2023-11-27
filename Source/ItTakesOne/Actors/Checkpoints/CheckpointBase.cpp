// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckpointBase.h"

#include "ItTakesOne/Actors/GameModes/PlayableGameModeBase.h"
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
	if (bWasActivated) { return; }

	if (const auto GameState = GetWorld()->GetGameState<APlayableGameStateBase>())
	{
		if (GameState->UpdateActiveSpawnPoint(SpawnPoint))
		{
			bWasActivated = true;
			if (const auto GameMode = GetWorld()->GetAuthGameMode<APlayableGameModeBase>())
			{
				GameMode->WriteSaveGame();
			}
		}
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

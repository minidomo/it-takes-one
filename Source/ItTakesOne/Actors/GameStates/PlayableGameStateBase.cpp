// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableGameStateBase.h"

#include "GameFramework/PlayerStart.h"
#include "ItTakesOne/Data/SaveGames/ContentSaveGame.h"
#include "ItTakesOne/Framework/MainWorldSettings.h"
#include "Kismet/GameplayStatics.h"

APlayableGameStateBase::APlayableGameStateBase()
{
}

void APlayableGameStateBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (const auto WorldSettings = Cast<AMainWorldSettings>(GetWorldSettings()))
	{
		ActiveSpawnPoint = WorldSettings->GetDefaultSpawnPoint();
		UE_LOG(LogTemp, Display, TEXT("%s: set active spawn point to world settings default spawn point: %d"),
		       *GetActorNameOrLabel(), !!ActiveSpawnPoint);
	}
}

bool APlayableGameStateBase::UpdateActiveSpawnPoint(APlayerStart* NewActiveSpawnPoint)
{
	if (NewActiveSpawnPoint == ActiveSpawnPoint)
	{
		return false;
	}

	const auto OldSpawnPoint = ActiveSpawnPoint;
	ActiveSpawnPoint = NewActiveSpawnPoint;
	OnActiveSpawnPointUpdateDelegate.Broadcast(OldSpawnPoint, ActiveSpawnPoint);
	UE_LOG(LogTemp, Display, TEXT("%s: updated spawn point"), *GetActorNameOrLabel());

	// test code
	if (const auto SaveGameInstance = Cast<UContentSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UContentSaveGame::StaticClass())))
	{
		UE_LOG(LogTemp, Display, TEXT("%s: created save game object"), *GetActorNameOrLabel());
		SaveGameInstance->ActiveCheckpointLabel = ActiveSpawnPoint->GetActorNameOrLabel();

		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, "Content", 0))
		{
			UE_LOG(LogTemp, Display, TEXT("%s: saved game"), *GetActorNameOrLabel());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: failed to save game"), *GetActorNameOrLabel());
		}
	}

	return true;
}

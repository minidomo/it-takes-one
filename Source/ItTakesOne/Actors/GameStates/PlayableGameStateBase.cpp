// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableGameStateBase.h"

#include "GameFramework/PlayerStart.h"
#include "ItTakesOne/Framework/MainWorldSettings.h"
#include "ItTakesOne/Libraries/DataLibrary.h"

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

	UDataLibrary::SaveWorld(this);

	return true;
}

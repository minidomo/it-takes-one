// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableGameStateBase.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "ItTakesOne/Framework/MainWorldSettings.h"

APlayableGameStateBase::APlayableGameStateBase()
{
}

void APlayableGameStateBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (!ActiveSpawnPoint)
	{
		if (const auto WorldSettings = Cast<AMainWorldSettings>(GetWorldSettings()))
		{
			UpdateActiveSpawnPoint(WorldSettings->GetDefaultSpawnPoint());
		}
	}
}

void APlayableGameStateBase::OnActorLoaded()
{
	ISavableActorInterface::OnActorLoaded();

	if (!ActiveSpawnPointName.IsNone())
	{
		if (!IsValid(ActiveSpawnPoint) || ActiveSpawnPointName != ActiveSpawnPoint->GetFName())
		{
			for (TActorIterator<APlayerStart> It(GetWorld(), APlayerStart::StaticClass()); It; ++It)
			{
				const auto Actor = *It;
				if (Actor->GetFName() == ActiveSpawnPointName)
				{
					UpdateActiveSpawnPoint(Actor);
					break;
				}
			}
		}
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
	ActiveSpawnPointName = ActiveSpawnPoint->GetFName();

	OnActiveSpawnPointUpdateDelegate.Broadcast(OldSpawnPoint, ActiveSpawnPoint);

	// UE_LOG(LogTemp, Display, TEXT("%s: updated spawn point %s"), *GetActorNameOrLabel(),
	//        *ActiveSpawnPoint->GetActorNameOrLabel());

	return true;
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "MainWorldSettings.h"

#include "Components/ShapeComponent.h"
#include "ItTakesOne/Actors/Checkpoints/CheckpointBase.h"
#include "Kismet/GameplayStatics.h"

AMainWorldSettings::AMainWorldSettings()
{
	bDisableDefaultSpawnPointWarning = false;
	bShowCheckpointAreas = false;
}

void AMainWorldSettings::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (!DefaultSpawnPoint)
	{
		if (!bDisableDefaultSpawnPointWarning)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: default spawn point is not set"), *GetActorNameOrLabel());
		}
	}
}

void AMainWorldSettings::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (bShowCheckpointAreas)
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(this, ACheckpointBase::StaticClass(), OutActors);

		for (const auto& Actor : OutActors)
		{
			const auto Checkpoint = Cast<ACheckpointBase>(Actor);
			Checkpoint->GetTriggerArea()->SetHiddenInGame(false);
		}
	}
}

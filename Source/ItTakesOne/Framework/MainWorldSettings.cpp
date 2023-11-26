// Fill out your copyright notice in the Description page of Project Settings.

#include "MainWorldSettings.h"

AMainWorldSettings::AMainWorldSettings()
{
	bDisableDefaultSpawnPointWarning = false;
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

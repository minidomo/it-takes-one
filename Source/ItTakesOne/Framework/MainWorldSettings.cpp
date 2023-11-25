// Fill out your copyright notice in the Description page of Project Settings.

#include "MainWorldSettings.h"

AMainWorldSettings::AMainWorldSettings()
{
}

void AMainWorldSettings::BeginPlay()
{
	Super::BeginPlay();
	if (!DefaultSpawnPoint)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: default spawn point is not set, which may be important"),
		       *GetActorNameOrLabel());
	}
}

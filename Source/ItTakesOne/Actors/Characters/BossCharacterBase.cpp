// Fill out your copyright notice in the Description page of Project Settings.

#include "BossCharacterBase.h"

ABossCharacterBase::ABossCharacterBase()
{
	BossName = "Default Boss Name";
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABossCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

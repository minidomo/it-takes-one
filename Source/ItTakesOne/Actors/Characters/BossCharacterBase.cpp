﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "BossCharacterBase.h"

ABossCharacterBase::ABossCharacterBase()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABossCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

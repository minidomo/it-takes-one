// Fill out your copyright notice in the Description page of Project Settings.

#include "RingWave.h"

ARingWave::ARingWave()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName("OverlapAll");

	PrimaryActorTick.bCanEverTick = true;
}

void ARingWave::BeginPlay()
{
	Super::BeginPlay();
}

void ARingWave::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

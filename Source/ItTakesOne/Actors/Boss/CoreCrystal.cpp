// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreCrystal.h"

#include "Components/BoxComponent.h"
#include "ItTakesOne/Actors/GameModes/SkyLandGameMode.h"

ACoreCrystal::ACoreCrystal()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = BoxComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	MaxTimeAlive = 15.f;
}

void ACoreCrystal::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ACoreCrystal::CallDestroy, MaxTimeAlive);
}

void ACoreCrystal::CallDestroy()
{
	Destroy();
}

void ACoreCrystal::Destroyed()
{
	Super::Destroyed();
	if (const auto GameMode = GetWorld()->GetAuthGameMode<ASkyLandGameMode>())
	{
		GameMode->OnCoreCrystalDestroyedDelegate.Broadcast();
	}
}

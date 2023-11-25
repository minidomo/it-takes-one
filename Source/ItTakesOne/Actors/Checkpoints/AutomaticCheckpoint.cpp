// Fill out your copyright notice in the Description page of Project Settings.

#include "AutomaticCheckpoint.h"

#include "Components/BoxComponent.h"
#include "ItTakesOne/ItTakesOneCharacter.h"

AAutomaticCheckpoint::AAutomaticCheckpoint()
{
	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerArea"));
	TriggerArea->SetupAttachment(RootComponent);
	UBoxComponent* Area = GetTriggerArea<UBoxComponent>();
	Area->InitBoxExtent({150, 150, 150});
}

void AAutomaticCheckpoint::BeginPlay()
{
	Super::BeginPlay();
	TriggerArea->OnComponentBeginOverlap.AddDynamic(this, &AAutomaticCheckpoint::OnComponentBeginOverlap);
}

void AAutomaticCheckpoint::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                   bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AItTakesOneCharacter::StaticClass()))
	{
		Activate();
	}
}

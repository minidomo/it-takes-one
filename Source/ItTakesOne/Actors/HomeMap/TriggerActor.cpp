// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATriggerActor::ATriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
	HitboxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	HitboxComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


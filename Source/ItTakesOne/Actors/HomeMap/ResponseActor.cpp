// Fill out your copyright notice in the Description page of Project Settings.


#include "ResponseActor.h"
#include "TriggerActor.h"

// Sets default values
AResponseActor::AResponseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent); 

}

// Called when the game starts or when spawned
void AResponseActor::BeginPlay()
{
	Super::BeginPlay();
	for (ATriggerActor* TriggerActor : TriggerActors)
    {
        if (TriggerActor)
        {
			TriggerActor->OnTriggerDelegate.AddDynamic(this, &AResponseActor::ResponseToTrigger);
		}
	}
}

// Called every frame
void AResponseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// If trigger activated, move myself
void AResponseActor::ResponseToTrigger() {
	for (ATriggerActor* TriggerActor : TriggerActors)
    {
        if (TriggerActor)
        {
			SetActorLocation(GetActorLocation() - GetActorUpVector() * 5.f);
		}
	}
}


// Fill out your copyright notice in the Description page of Project Settings
#include "ClockHandActor.h"
#include "Engine/Engine.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ItTakesOne/ItTakesOneCharacter.h"

// Sets default values
AClockHandActor::AClockHandActor()
{
    // Set this actor to call Tick() every frame. 
    PrimaryActorTick.bCanEverTick = true;

    PivotComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PivotComponent"));
    RootComponent = PivotComponent;

    ClockHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClockHandMesh"));
    ClockHandMesh->SetupAttachment(RootComponent);


    // Adjust the position of ClockHandMesh so that its rotation point aligns with PivotComponent's origin

    RotationSpeed = 30.0f;
}

// Called when the game starts or when spawned
void AClockHandActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AClockHandActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

   
    RotateHand(DeltaTime);
    OnOverlapBegin();
   
}

void AClockHandActor::RotateHand(float DeltaTime)
{
    FRotator NewRotation = PivotComponent->GetComponentRotation();
    NewRotation.Yaw += RotationSpeed * DeltaTime;
    PivotComponent->SetWorldRotation(NewRotation);
}

void AClockHandActor::OnOverlapBegin()
{
    // Check if the OtherActor is not null and not equal to this actor
    TArray<AActor*> OverlappingActors;

    GetOverlappingActors(OverlappingActors);

    // Loop through each actor
    for (AActor* Actor : OverlappingActors)
    {
        // Check if the actor is of the BreakableActor class
        AItTakesOneCharacter* Character = Cast<AItTakesOneCharacter>(Actor);
        if (Character)
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character may die"));
            }
            //character die
            Character->Destroyed();
        }
    }
}
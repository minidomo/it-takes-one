// Fill out your copyright notice in the Description page of Project Settings
#include "ClockHandActor.h"
#include "Engine/Engine.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
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
   
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(PivotComponent);
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AClockHandActor::OnOverlapBegin);


    // Adjust the position of ClockHandMesh so that its rotation point aligns with PivotComponent's origin
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
   
}

void AClockHandActor::RotateHand(float DeltaTime)
{
    FRotator NewRotation = PivotComponent->GetComponentRotation();
    NewRotation.Yaw += RotationSpeed * DeltaTime;
    PivotComponent->SetWorldRotation(NewRotation);
}

void AClockHandActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the actor is of the BreakableActor class
        AItTakesOneCharacter* Character = Cast<AItTakesOneCharacter>(OtherActor);
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
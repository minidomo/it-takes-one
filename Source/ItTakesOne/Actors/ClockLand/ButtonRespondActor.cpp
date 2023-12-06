// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonRespondActor.h"
#include "ButtonActor.h"
#include "../LevelTransitionActor.h"
#include "Components/TextRenderComponent.h"
#include "EngineUtils.h"
#include "Engine/Engine.h"

// Sets default values
AButtonRespondActor::AButtonRespondActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RespondMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RespondMesh"));
    RootComponent = RespondMesh;
    
    TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
    TextComponent->SetupAttachment(RespondMesh); // Attach to your board mesh
    TextComponent->SetVisibility(false);

    TextComponent->SetText(FText::FromString("Backtrace To the Origin"));
    TextComponent->SetTextRenderColor(FColor::White);
    TextComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);

    bIsElevating = false;
    CurrentElevationTime = 0.0f;
    TargetElevation = 1000.0f;

    OriginalLocation = RespondMesh->GetComponentLocation();
    TargetLocation = OriginalLocation + FVector(0, 0, TargetElevation);
    bShouldElevate = true; // Start with elevating
}

// Called when the game starts or when spawned
void AButtonRespondActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtonRespondActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
   
    if (IsPlane)
    {
        if (bIsElevating) {
            CurrentElevationTime += DeltaTime;
            float Alpha = FMath::Clamp(CurrentElevationTime / TotalElevationTime, 0.0f, 1.0f);
            FVector NewLocation = FMath::Lerp(OriginalLocation, TargetLocation, Alpha);
            RespondMesh->SetWorldLocation(NewLocation);

            if (Alpha >= 1.0f)
            {
                bIsElevating = false;
                CurrentElevationTime = 0.0f;

                // Toggle the direction of elevation only after completing the current movement
                bShouldElevate = !bShouldElevate;
            }
        }
        
        if (ConnectedButtons.Num() > 0 && ConnectedButtons[0])
        {
            FVector CurrentButtonLocation = ConnectedButtons[0]->GetActorLocation();
            FVector NewButtonLocation = FVector(CurrentButtonLocation.X, CurrentButtonLocation.Y, GetActorLocation().Z-60);

            ConnectedButtons[0]->SetActorLocation(NewButtonLocation);
        }
    }
   
    CheckButtons();
}

void AButtonRespondActor::CheckButtons()
{


    for (AButtonActor* Button : ConnectedButtons)
    {
        if (Button && !Button->bIsActivated)
        {
            return;
        }
    }

    if (IsPlane) {
        if (bIsElevating)
        {
            return;
        }
        ElevatePlane();
    }
    else if (IsSpawn) {
        MakeVisible();
    }
    else if (IsBoard) {
        ShowBoard();
    }
}


void AButtonRespondActor::ElevatePlane()
{
    if (!bIsElevating)
    {
        // Update the target location based on the current elevation direction
        if (bShouldElevate) {
            OriginalLocation = RespondMesh->GetComponentLocation();
            TargetLocation = OriginalLocation + FVector(0, 0, TargetElevation);
        }
        else {
            OriginalLocation = RespondMesh->GetComponentLocation();
            TargetLocation = OriginalLocation - FVector(0, 0, TargetElevation);
        
        }

        bIsElevating = true;
    }
}


void  AButtonRespondActor::MakeVisible() {
    if (RootComponent && RootComponent->IsA(UStaticMeshComponent::StaticClass()))
    {
        
        Cast<UStaticMeshComponent>(RootComponent)->SetVisibility(true);
        SetActorHiddenInGame(false);
        RespondMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }
}

void  AButtonRespondActor::ShowBoard() {
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("showboard"));
    }

    if (RootComponent && RootComponent->IsA(UStaticMeshComponent::StaticClass()))
    {

        Cast<UStaticMeshComponent>(RootComponent)->SetVisibility(true);
        SetActorHiddenInGame(false);
        RespondMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }

    TextComponent->SetVisibility(true);
    TextComponent->SetText(FText::FromString("Backtrace To the Origin"));

    for (TActorIterator<ALevelTransitionActor> It(GetWorld()); It; ++It)
    {
        ALevelTransitionActor* LevelTransitionActor = *It;
        if (LevelTransitionActor)
        {
            // Make sure we're working with the correct actor if there are any filters or checks to be done.

            // Make the LevelTransitionActor visible.
            LevelTransitionActor->SetActorHiddenInGame(false);
            LevelTransitionActor->SetActorEnableCollision(true);
            LevelTransitionActor->SetActorTickEnabled(true); // If you want the actor to start ticking (if it has any ticking logic that needs to run)

            // Optionally, if the LevelTransitionActor has any specific components that also need to be made visible:
            UStaticMeshComponent* MeshComponent = LevelTransitionActor->FindComponentByClass<UStaticMeshComponent>();
            if (MeshComponent)
            {
                MeshComponent->SetVisibility(true);
                MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            }

            // Assuming there is only one LevelTransitionActor, we can break the loop after making it visible.
            break;
        }
    }
}


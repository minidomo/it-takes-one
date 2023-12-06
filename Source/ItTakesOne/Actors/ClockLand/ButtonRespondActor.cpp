// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonRespondActor.h"
#include "ButtonActor.h"
#include "Components/TextRenderComponent.h"
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
    TargetElevation = 1000.0f; // Adjust as necessary
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
   
    if (IsPlane) {
        if (bIsElevating)
        {
            CurrentElevationTime += DeltaTime;
            float Alpha = FMath::Clamp(CurrentElevationTime / TotalElevationTime, 0.0f, 1.0f);
            FVector NewLocation = FMath::Lerp(OriginalLocation, TargetLocation, Alpha);
            RespondMesh->SetWorldLocation(NewLocation);

            if (Alpha >= 1.0f)
            {
                bIsElevating = false;
                CurrentElevationTime = 0.0f;
            }
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
        ElevatePlane();
    }
    else if (IsSpawn) {
        MakeVisible();
    }
    else if (IsBoard) {
        ShowBoard();
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
}





void AButtonRespondActor::ElevatePlane()
{
    if (!bIsElevating)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("elevateplane"));
        }

        bIsElevating = true;
        OriginalLocation = RespondMesh->GetComponentLocation();
        TargetLocation = OriginalLocation + FVector(0, 0, TargetElevation);
    }

}
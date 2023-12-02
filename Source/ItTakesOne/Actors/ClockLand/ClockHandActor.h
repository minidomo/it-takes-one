// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "ClockHandActor.generated.h"

UCLASS()
class ITTAKESONE_API AClockHandActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AClockHandActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Static mesh for the clock hand
    UPROPERTY(VisibleAnywhere)
        UStaticMeshComponent* ClockHandMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        USceneComponent* PivotComponent;

    // Rotation speed in degrees per second
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClockHand")
        float RotationSpeed;

private:
    // Handles the rotation logic
    void RotateHand(float DeltaTime);

    UFUNCTION()
        void OnOverlapBegin();
};
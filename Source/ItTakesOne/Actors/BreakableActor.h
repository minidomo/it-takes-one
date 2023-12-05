// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItTakesOne/Interfaces/SavableActorInterface.h"
#include "BreakableActor.generated.h"

UCLASS()
class ITTAKESONE_API ABreakableActor : public AActor, public ISavableActorInterface
{
    GENERATED_BODY()

public:
    ABreakableActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        class UStaticMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere)
        class UBoxComponent* CollisionBox;

};

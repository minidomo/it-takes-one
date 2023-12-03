// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItTakesOne/Interfaces/SavableActorInterface.h"
#include "RingWave.generated.h"

UCLASS()
class ITTAKESONE_API ARingWave : public AActor, public ISavableActorInterface
{
	GENERATED_BODY()

public:
	ARingWave();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
};

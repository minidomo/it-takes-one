// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckpointBase.h"
#include "AutomaticCheckpoint.generated.h"

UCLASS()
class ITTAKESONE_API AAutomaticCheckpoint : public ACheckpointBase
{
	GENERATED_BODY()

public:
	AAutomaticCheckpoint();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult);
};

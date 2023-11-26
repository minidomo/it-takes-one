// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointBase.generated.h"

class APlayerStart;

UCLASS(Abstract)
class ITTAKESONE_API ACheckpointBase : public AActor
{
	GENERATED_BODY()

public:
	ACheckpointBase();

protected:
	UPROPERTY(VisibleAnywhere)
	UShapeComponent* TriggerArea;

	UPROPERTY(EditInstanceOnly, Category = Spawn)
	APlayerStart* SpawnPoint;

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE UShapeComponent* GetTriggerArea() const { return TriggerArea; }

	template <class T>
	FORCEINLINE T* GetTriggerArea() const { return Cast<T>(TriggerArea); }

	FORCEINLINE APlayerStart* GetSpawnPoint() const { return SpawnPoint; }

	virtual void Activate();
	virtual bool IsActive();
};

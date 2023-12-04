// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItTakesOne/Interfaces/SavableActorInterface.h"
#include "CoreCrystal.generated.h"

UCLASS()
class ITTAKESONE_API ACoreCrystal : public AActor, public ISavableActorInterface
{
	GENERATED_BODY()

public:
	ACoreCrystal();

private:
	FTimerHandle DestroyTimerHandle;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, SaveGame)
	float MaxTimeAlive;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void CallDestroy();

public:
	virtual void Destroyed() override;
};

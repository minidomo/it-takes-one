// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItTakesOne/Interfaces/SavableActorInterface.h"
#include "CoreCrystal.generated.h"

class UBoxComponent;

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

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, SaveGame)
	float MaxTimeAlive;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void CallDestroy();

public:
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }
	FORCEINLINE UBoxComponent* GetBoxComponent() const { return BoxComponent; }

	virtual void Destroyed() override;
};

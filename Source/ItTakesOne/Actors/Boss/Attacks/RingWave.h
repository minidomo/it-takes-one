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

private:
	FTimerHandle DestroyTimeHandle;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(SaveGame)
	FVector Direction;

	UPROPERTY(EditAnywhere, SaveGame)
	float Speed;

	UPROPERTY(EditAnywhere, SaveGame)
	float PlayerDamage;

	UPROPERTY(EditAnywhere, SaveGame)
	float MaxTimeAlive;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void CallDestroy();

public:
	virtual void Tick(float DeltaSeconds) override;

	void SetDirection(const FVector& NewDirection);
	void SetSpeed(float NewSpeed);
	void SetPlayerDamage(float NewPlayerDamage);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItTakesOne/Interfaces/SavableActorInterface.h"
#include "LevelTransitionActor.generated.h"

UCLASS()
class ITTAKESONE_API ALevelTransitionActor : public AActor, public ISavableActorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelTransitionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollisionComponent;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* VisualComponent;

	UPROPERTY(EditAnywhere, Category = "Level", SaveGame)
	FName LevelToLoad;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

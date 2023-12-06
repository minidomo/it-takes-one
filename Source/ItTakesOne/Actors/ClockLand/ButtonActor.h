// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ItTakesOne/Interfaces/SavableActorInterface.h"
#include "ButtonActor.generated.h"

UCLASS()
class ITTAKESONE_API AButtonActor : public AActor, public ISavableActorInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonActor();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ButtonMesh;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* CollisionBox;

	UPROPERTY(SaveGame)
	bool bIsActivated;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FTimerHandle TimerHandle;

	float ButtonElevation = 0.f;
	FVector InitialButtonLocation;
	const float MaxElevation = 1000.f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void DeactivateButton();


};

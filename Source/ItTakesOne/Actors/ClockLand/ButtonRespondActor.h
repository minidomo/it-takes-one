// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonActor.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "ButtonRespondActor.generated.h"

UCLASS()
class ITTAKESONE_API AButtonRespondActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonRespondActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UTextRenderComponent* TextComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CheckButtons();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* RespondMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TArray<AButtonActor*> ConnectedButtons;

	FTimerHandle DoorTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		bool IsPlane;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		bool IsSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		bool IsBoard;

	void ElevatePlane();

	void MakeVisible();

	void ShowBoard();

private:
	// Flag to check if the plane has already elevated
	bool bIsElevating;

	// Target elevation height
	float TargetElevation;

	// Current elevation progress
	float CurrentElevationTime;

	// Total time for elevation
	const float TotalElevationTime = 3.0f; // 3 seconds

	// Original location of the plane
	FVector OriginalLocation;

	// Target location of the plane
	FVector TargetLocation;

};

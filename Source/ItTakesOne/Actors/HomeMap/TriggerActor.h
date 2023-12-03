// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerDelegate);

UCLASS()
class ITTAKESONE_API ATriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerActor();

	FORCEINLINE class USphereComponent* GetHitBoxComponent() const { return HitboxComponent; }
	FORCEINLINE class UStaticMeshComponent* GetMeshComponent() const { return MeshComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "World Pawn")
	class USphereComponent* HitboxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "World Pawn")
	class UStaticMeshComponent* MeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "Trigger")
	FTriggerDelegate OnTriggerDelegate;

};

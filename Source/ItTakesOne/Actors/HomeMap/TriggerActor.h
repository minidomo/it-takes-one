// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItTakesOne/Interfaces/SavableActorInterface.h"
#include "TriggerActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerDelegate);

UCLASS()
class ITTAKESONE_API ATriggerActor : public AActor, public ISavableActorInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerActor();

	FORCEINLINE class UBoxComponent* GetHitBoxComponent() const { return HitboxComponent; }
	FORCEINLINE class UStaticMeshComponent* GetMeshComponent() const { return MeshComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger")
	class UBoxComponent* HitboxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger")
	class UStaticMeshComponent* MeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "Trigger")
	FTriggerDelegate OnTriggerDelegate;

};

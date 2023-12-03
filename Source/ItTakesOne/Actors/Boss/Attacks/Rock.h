// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItTakesOne/Interfaces/SavableActorInterface.h"
#include "Rock.generated.h"

UCLASS()
class ITTAKESONE_API ARock : public AActor, public ISavableActorInterface
{
	GENERATED_BODY()

public:
	ARock();

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
	float BossDamage;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnBossDestroyed(AActor* DestroyedActor);

public:
	virtual void Tick(float DeltaTime) override;

	void SetDirection(const FVector& NewDirection);
	void SetSpeed(float NewSpeed);
	void SetPlayerDamage(float NewPlayerDamage);
	void SetBossDamage(float NewBossDamage);
};

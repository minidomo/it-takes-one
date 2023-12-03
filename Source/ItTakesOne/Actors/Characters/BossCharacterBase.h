// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ItTakesOne/Interfaces/SavableActorInterface.h"
#include "BossCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackCompleteDelegate);

class UBehaviorTree;

UCLASS()
class ITTAKESONE_API ABossCharacterBase : public ACharacter, public ISavableActorInterface
{
	GENERATED_BODY()

public:
	ABossCharacterBase();

protected:
	UPROPERTY(EditAnywhere, SaveGame)
	FString BossName;

public:
	UPROPERTY()
	FOnAttackCompleteDelegate OnAttackCompleteDelegate;

	UPROPERTY(EditAnywhere, Category = AI)
	UBehaviorTree* BehaviorTree;

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE FString GetBossName() const { return BossName; }
};

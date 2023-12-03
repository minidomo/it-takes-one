// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossControllerBase.h"
#include "WindBossController.generated.h"

UCLASS()
class ITTAKESONE_API AWindBossController : public ABossControllerBase
{
	GENERATED_BODY()

public:
	AWindBossController();

public:
	UPROPERTY(EditAnywhere, SaveGame)
	FName ActionNameKey;

	UPROPERTY(EditAnywhere, SaveGame)
	FName ReadyKey;

protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void OnAttackComplete() override;

	TArray<FName> GetAttackOptions();
	FName GetRandomAttack();
	void ExecuteAttack(FName AttackName);
};

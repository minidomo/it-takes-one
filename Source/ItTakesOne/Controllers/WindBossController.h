// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossControllerBase.h"
#include "ItTakesOne/Actors/Characters/WindBossCharacter.h"
#include "WindBossController.generated.h"

UCLASS()
class ITTAKESONE_API AWindBossController : public ABossControllerBase
{
	GENERATED_BODY()

public:
	AWindBossController();

public:
	UPROPERTY(EditAnywhere, SaveGame)
	FName ActionKey;

	UPROPERTY(EditAnywhere, SaveGame)
	FName ReadyKey;

protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void OnAttackComplete() override;

	EWindBossAttack GetRandomAttack();
	void ExecuteAttack(EWindBossAttack Attack);
};

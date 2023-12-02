// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossControllerBase.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class ITTAKESONE_API ABossControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	ABossControllerBase();

protected:
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTree;

protected:
	virtual void OnPossess(APawn* InPawn) override;
};

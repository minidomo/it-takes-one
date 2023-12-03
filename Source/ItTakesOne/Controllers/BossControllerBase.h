// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ItTakesOne/Interfaces/SavableActorInterface.h"
#include "BossControllerBase.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class ITTAKESONE_API ABossControllerBase : public AAIController, public ISavableActorInterface
{
	GENERATED_BODY()

public:
	ABossControllerBase();

private:
	FTimerHandle StartAITimerHandle;

protected:
	UPROPERTY(VisibleAnywhere)
	UBehaviorTreeComponent* BehaviorTree;

	UPROPERTY(EditAnywhere, SaveGame)
	float StartAIDelay;

protected:
	UFUNCTION()
	void StartAI();

protected:
	virtual void OnPossess(APawn* InPawn) override;
};

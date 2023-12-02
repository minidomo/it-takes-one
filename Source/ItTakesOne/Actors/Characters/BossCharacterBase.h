// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossCharacterBase.generated.h"

class UBehaviorTree;

UCLASS()
class ITTAKESONE_API ABossCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ABossCharacterBase();

	UPROPERTY(EditAnywhere, Category = AI)
	UBehaviorTree* BehaviorTree;

protected:
	virtual void BeginPlay() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChooseAction.generated.h"

UCLASS()
class ITTAKESONE_API UBTTask_ChooseAction : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ChooseAction();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChooseAction.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "ItTakesOne/Controllers/WindBossController.h"

EBTNodeResult::Type UBTTask_ChooseAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto Controller = Cast<AWindBossController>(OwnerComp.GetAIOwner()))
	{
		const auto Blackboard = Controller->GetBlackboardComponent();

		if (Blackboard->GetValueAsBool(Controller->ReadyKey))
		{
			Blackboard->SetValueAsName(Controller->ActionNameKey, Controller->GetRandomAttack());
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

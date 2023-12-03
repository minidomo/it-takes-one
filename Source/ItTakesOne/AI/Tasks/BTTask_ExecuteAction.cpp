// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ExecuteAction.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "ItTakesOne/Controllers/WindBossController.h"

EBTNodeResult::Type UBTTask_ExecuteAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto Controller = Cast<AWindBossController>(OwnerComp.GetAIOwner()))
	{
		const auto Blackboard = Controller->GetBlackboardComponent();
		Blackboard->SetValueAsBool(Controller->ReadyKey, false);
		Controller->ExecuteAttack(Blackboard->GetValueAsName(Controller->ActionNameKey));
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

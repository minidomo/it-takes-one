// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ExecuteAction.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "ItTakesOne/Controllers/WindBossController.h"

UBTTask_ExecuteAction::UBTTask_ExecuteAction()
{
	NodeName = "ExecuteAction";
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UBTTask_ExecuteAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto Controller = Cast<AWindBossController>(OwnerComp.GetAIOwner()))
	{
		const auto Blackboard = Controller->GetBlackboardComponent();
		Blackboard->SetValueAsBool(Controller->ReadyKey, false);
		Controller->ExecuteAttack(StaticCast<EWindBossAttack>(Blackboard->GetValueAsEnum(Controller->ActionKey)));
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

void UBTTask_ExecuteAction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (const auto Controller = Cast<AWindBossController>(OwnerComp.GetAIOwner()))
	{
		const auto Blackboard = Controller->GetBlackboardComponent();
		if (Blackboard->GetValueAsBool(Controller->ReadyKey))
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

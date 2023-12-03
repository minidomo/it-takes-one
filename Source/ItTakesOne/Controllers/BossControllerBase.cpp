// Fill out your copyright notice in the Description page of Project Settings.

#include "BossControllerBase.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ItTakesOne/Actors/Characters/BossCharacterBase.h"

ABossControllerBase::ABossControllerBase()
{
	BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));

	StartAIDelay = 3.f;
}

void ABossControllerBase::StartAI()
{
	if (const auto AICharacter = Cast<ABossCharacterBase>(GetPawn()))
	{
		if (const auto Tree = AICharacter->BehaviorTree)
		{
			if (Tree->BlackboardAsset)
			{
				BehaviorTree->StartTree(*Tree);
			}
		}
	}
}

void ABossControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const auto AICharacter = Cast<ABossCharacterBase>(InPawn))
	{
		if (const auto Tree = AICharacter->BehaviorTree)
		{
			if (Tree->BlackboardAsset)
			{
				Blackboard->InitializeBlackboard(*Tree->BlackboardAsset);
				GetWorldTimerManager().SetTimer(StartAITimerHandle, this, &ABossControllerBase::StartAI, StartAIDelay);
			}
		}
	}
}

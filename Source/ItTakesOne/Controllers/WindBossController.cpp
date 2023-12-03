// Fill out your copyright notice in the Description page of Project Settings.

#include "WindBossController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "ItTakesOne/Actors/Characters/WindBossCharacter.h"

AWindBossController::AWindBossController()
{
	ActionNameKey = "ActionName";
	ReadyKey = "Ready";
}

void AWindBossController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Blackboard->SetValueAsBool(ReadyKey, true);
}

void AWindBossController::OnAttackComplete()
{
	Super::OnAttackComplete();
	Blackboard->SetValueAsBool(ReadyKey, true);
}

TArray<FName> AWindBossController::GetAttackOptions()
{
	TArray<FName> Options;

	// Options.Add("ring-wave");
	Options.Add("rock-throw");

	const auto BossCharacter = Cast<AWindBossCharacter>(GetCharacter());
	const auto HealthPerecentage = BossCharacter->GetHealth() / BossCharacter->GetMaxHealth();

	if (HealthPerecentage < .5)
	{
		Options.Add("wind-blast-and-rock-throw");
	}

	return Options;
}

FName AWindBossController::GetRandomAttack()
{
	const auto Options = GetAttackOptions();
	const int32 Index = FMath::RandHelper(Options.Num());
	return Options[Index];
}

void AWindBossController::ExecuteAttack(FName AttackName)
{
	const auto BossCharacter = Cast<AWindBossCharacter>(GetCharacter());

	if (AttackName == "ring-wave")
	{
		BossCharacter->RingWaveAttack();
	}
	else if (AttackName == "rock-throw")
	{
		BossCharacter->RockThrowAttack();
	}
	else if (AttackName == "wind-blast-and-rock-throw")
	{
		BossCharacter->WindBlastAndRockThrowAttack();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "WindBossController.h"

#include "BehaviorTree/BlackboardComponent.h"

AWindBossController::AWindBossController()
{
	ActionKey = "Action";
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

EWindBossAttack AWindBossController::GetRandomAttack()
{
	const auto BossCharacter = Cast<AWindBossCharacter>(GetCharacter());
	const auto HealthPerecentage = BossCharacter->GetHealth() / BossCharacter->GetMaxHealth();

	EWindBossAttack Ret;
	const float V = FMath::FRand();

	if (HealthPerecentage < .5)
	{
		if (V < .4)
		{
			Ret = EWindBossAttack::RingWave;
		}
		else
		{
			Ret = EWindBossAttack::RockThrow;
		}
	}
	else
	{
		if (V < .25)
		{
			Ret = EWindBossAttack::RingWave;
		}
		else
		{
			Ret = EWindBossAttack::RockThrow;
		}
	}

	return Ret;
}

void AWindBossController::ExecuteAttack(EWindBossAttack Attack)
{
	const auto BossCharacter = Cast<AWindBossCharacter>(GetCharacter());

	if (Attack == EWindBossAttack::RingWave)
	{
		BossCharacter->RingWaveAttackSequence();
	}
	else if (Attack == EWindBossAttack::RockThrow)
	{
		BossCharacter->RockThrowAttackSequence();
	}
}

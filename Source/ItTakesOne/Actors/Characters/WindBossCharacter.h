// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossCharacterBase.h"
#include "WindBossCharacter.generated.h"

UCLASS()
class ITTAKESONE_API AWindBossCharacter : public ABossCharacterBase
{
	GENERATED_BODY()

public:
	AWindBossCharacter();

protected:
	virtual void BeginPlay() override;
};

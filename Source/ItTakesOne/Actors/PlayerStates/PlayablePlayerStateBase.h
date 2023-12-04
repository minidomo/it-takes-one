// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ItTakesOne/Interfaces/SavableActorInterface.h"
#include "PlayablePlayerStateBase.generated.h"

UCLASS()
class ITTAKESONE_API APlayablePlayerStateBase : public APlayerState, public ISavableActorInterface
{
	GENERATED_BODY()

public:
	APlayablePlayerStateBase();

public:
	virtual void OnActorLoaded() override;
};

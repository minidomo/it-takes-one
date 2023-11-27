// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItTakesOne/Data/SaveGames/ContentSaveGame.h"
#include "UObject/Interface.h"
#include "SavableActorInterface.generated.h"

UINTERFACE()
class USavableActorInterface : public UInterface
{
	GENERATED_BODY()
};

class ITTAKESONE_API ISavableActorInterface
{
	GENERATED_BODY()

public:
	virtual void OnActorLoaded();
	virtual void ImportActorData(const FActorSaveData& In);
	virtual void ExportActorData(FActorSaveData& Out);
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "SkyLandGameMode.h"
#include "ItTakesOne/Framework/MainGameInstance.h"

ASkyLandGameMode::ASkyLandGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/Blueprints/BPSkyController"));
	if (PlayerControllerBPClass.Class)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

FPlayableWorldSaveData* ASkyLandGameMode::GetPlayableWorldSaveData()
{
	const auto GameInstance = GetGameInstance<UMainGameInstance>();
	const auto ContentData = GameInstance->GetContentData();
	return &ContentData->SkyLand;
}

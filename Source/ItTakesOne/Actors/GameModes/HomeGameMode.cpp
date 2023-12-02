// Fill out your copyright notice in the Description page of Project Settings.

#include "HomeGameMode.h"
#include "ItTakesOne/Framework/MainGameInstance.h"

AHomeGameMode::AHomeGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/Blueprints/BPHomeController"));
	if (PlayerControllerBPClass.Class)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

FPlayableWorldSaveData* AHomeGameMode::GetPlayableWorldSaveData()
{
	const auto GameInstance = GetGameInstance<UMainGameInstance>();
	const auto ContentData = GameInstance->GetContentData();
	return &ContentData->Home;
}

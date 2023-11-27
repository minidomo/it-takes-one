// Fill out your copyright notice in the Description page of Project Settings.


#include "ClockLandGameMode.h"
#include "ItTakesOne/Framework/MainGameInstance.h"

class UMainGameInstance;

AClockLandGameMode::AClockLandGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/Blueprints/BPClockController"));
	if (PlayerControllerBPClass.Class)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

FPlayableWorldSaveData* AClockLandGameMode::GetPlayableWorldSaveData()
{
	const auto GameInstance = GetGameInstance<UMainGameInstance>();
	const auto ContentData = GameInstance->GetContentData();
	return &ContentData->ClockLand;
}

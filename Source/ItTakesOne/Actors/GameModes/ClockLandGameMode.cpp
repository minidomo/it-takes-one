// Fill out your copyright notice in the Description page of Project Settings.


#include "ClockLandGameMode.h"

#include "ItTakesOne/ItTakesOneCharacter.h"
#include "ItTakesOne/Framework/MainGameInstance.h"

AClockLandGameMode::AClockLandGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/Blueprints/BPClockController"));
	if (PlayerControllerBPClass.Class)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void AClockLandGameMode::OnPlayerDied(ACharacter* Character, AController* Controller)
{
	Super::OnPlayerDied(Character, Controller);
	if (const auto NewCharacter = Cast<AItTakesOneCharacter>(Controller->GetCharacter()))
	{
		NewCharacter->StartPositionRecording();
	}
}

FPlayableWorldSaveData* AClockLandGameMode::GetPlayableWorldSaveData()
{
	if (const auto GameInstance = GetGameInstance<UMainGameInstance>())
	{
		const auto ContentData = GameInstance->GetContentData();
		return &ContentData->ClockLand;
	}
	return nullptr;
}

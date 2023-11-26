// Fill out your copyright notice in the Description page of Project Settings.

#include "SkyLandGameMode.h"
#include "ItTakesOne/ItTakesOneCharacter.h"

ASkyLandGameMode::ASkyLandGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BPSkyController"));
    if (PlayerControllerBPClass.Class)
    {
        PlayerControllerClass = PlayerControllerBPClass.Class;
    }
}

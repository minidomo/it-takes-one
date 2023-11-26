// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameInstance.h"

#include "ItTakesOne/Data/SaveGames/ContentSaveGame.h"
#include "Kismet/GameplayStatics.h"

UMainGameInstance::UMainGameInstance()
{
}

void UMainGameInstance::Init()
{
	Super::Init();
	/*
	 * load save file
	 */
	UE_LOG(LogTemp, Display, TEXT("%s: init"), *GetName());

	if (const auto SaveGameInstance = Cast<UContentSaveGame>(UGameplayStatics::LoadGameFromSlot("Content", 0)))
	{
		UE_LOG(LogTemp, Display, TEXT("%s: loaded: %s"), *GetName(), *SaveGameInstance->ActiveCheckpointLabel);
	}
}

void UMainGameInstance::Shutdown()
{
	Super::Shutdown();
	UE_LOG(LogTemp, Display, TEXT("%s: shutdown"), *GetName());
}

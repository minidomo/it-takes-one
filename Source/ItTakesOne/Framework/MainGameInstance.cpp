// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameInstance.h"

#include "ItTakesOne/Data/SaveGames/ContentSaveGame.h"
#include "ItTakesOne/Data/SaveGames/SettingsSaveGame.h"
#include "ItTakesOne/Libraries/DataLibrary.h"
#include "Kismet/GameplayStatics.h"

UMainGameInstance::UMainGameInstance()
{
	SettingsSlotName = "Settings";
	ContentSlotName = "Content";
}

void UMainGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Display, TEXT("%s: init"), *GetName());

	ContentData = Cast<UContentSaveGame>(
		UDataLibrary::LoadOrCreateGame(UContentSaveGame::StaticClass(), ContentSlotName));
	SettingsData = Cast<USettingsSaveGame>(
		UDataLibrary::LoadOrCreateGame(USettingsSaveGame::StaticClass(), SettingsSlotName));

	if (ContentData)
	{
		UE_LOG(LogTemp, Display, TEXT("%s: loaded %s.sav"), *GetName(), *ContentSlotName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s: issue loading %s.sav"), *GetName(), *ContentSlotName);
	}

	if (SettingsData)
	{
		UE_LOG(LogTemp, Display, TEXT("%s: loading %s.sav"), *GetName(), *SettingsSlotName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s: issue loading %s.sav"), *GetName(), *SettingsSlotName);
	}
}

void UMainGameInstance::Shutdown()
{
	Super::Shutdown();
	UE_LOG(LogTemp, Display, TEXT("%s: shutdown"), *GetName());
}

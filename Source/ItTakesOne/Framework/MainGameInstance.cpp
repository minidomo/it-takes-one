// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameInstance.h"

#include "ItTakesOne/Data/SaveGames/ContentSaveGame.h"
#include "ItTakesOne/Data/SaveGames/SettingsSaveGame.h"
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
		LoadOrCreateSaveGame(UContentSaveGame::StaticClass(), ContentSlotName));
	SettingsData = Cast<USettingsSaveGame>(
		LoadOrCreateSaveGame(USettingsSaveGame::StaticClass(), SettingsSlotName));

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
	UE_LOG(LogTemp, Display, TEXT("%s: shutdown\n "), *GetName());
}

USaveGame* UMainGameInstance::LoadOrCreateSaveGame(TSubclassOf<USaveGame> SaveGameClass, const FString& SlotName,
                                                   const int32 UserIndex)
{
	USaveGame* SaveGameInstance = UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex);

	if (!SaveGameInstance)
	{
		UE_LOG(LogTemp, Display, TEXT("making new file for %s"), *SlotName);
		SaveGameInstance = UGameplayStatics::CreateSaveGameObject(SaveGameClass);
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, UserIndex);
	}

	return SaveGameInstance;
}

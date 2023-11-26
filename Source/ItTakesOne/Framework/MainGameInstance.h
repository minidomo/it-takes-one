// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

class UContentSaveGame;
class USettingsSaveGame;

UCLASS()
class ITTAKESONE_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMainGameInstance();

protected:
	UPROPERTY()
	USettingsSaveGame* SettingsData;

	UPROPERTY()
	UContentSaveGame* ContentData;

	UPROPERTY(EditAnywhere)
	FString SettingsSlotName;

	UPROPERTY(EditAnywhere)
	FString ContentSlotName;

public:
	virtual void Init() override;
	virtual void Shutdown() override;

	FORCEINLINE USettingsSaveGame* GetSettingsData() const { return SettingsData; }
	FORCEINLINE UContentSaveGame* GetContentData() const { return ContentData; }
	FORCEINLINE FString GetSettingsSlotName() const { return SettingsSlotName; }
	FORCEINLINE FString GetContentSlotName() const { return ContentSlotName; }
};

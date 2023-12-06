// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

class USaveGame;
class UContentSaveGame;

UCLASS()
class ITTAKESONE_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMainGameInstance();

protected:
	UPROPERTY()
	UContentSaveGame* ContentData;

	UPROPERTY(EditAnywhere)
	FString ContentSlotName;

public:
	virtual void Init() override;
	virtual void Shutdown() override;

	FORCEINLINE UContentSaveGame* GetContentData() const { return ContentData; }
	FORCEINLINE FString GetContentSlotName() const { return ContentSlotName; }

	static USaveGame* LoadOrCreateSaveGame(TSubclassOf<USaveGame> SaveGameClass, const FString& SlotName,
	                                       const int32 UserIndex = 0);
};

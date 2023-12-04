// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

UCLASS()
class ITTAKESONE_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainMenuGameMode();

protected:
	UPROPERTY(EditAnywhere, Category = "Class Type")
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UMainMenuUI* MainMenuWidget;

	virtual void BeginPlay() override;
};

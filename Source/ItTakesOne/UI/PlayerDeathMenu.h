// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerDeathMenu.generated.h"

class UButton;

UCLASS()
class ITTAKESONE_API UPlayerDeathMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* RestartButton;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnMainMenuButtonClick();

	UFUNCTION()
	void OnRestartButtonClick();
};

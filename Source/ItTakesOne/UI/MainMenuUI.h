// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MainMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESONE_API UMainMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	// Button Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(EditAnywhere, Category = "Class Type")
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UMainMenuUI* MapMenuWidget;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnStartButtonClick();

	UFUNCTION()
	void OnQuitButtonClick();
};

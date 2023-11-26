// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PauseUI.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESONE_API UPauseUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Button Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* MapSelectionButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* MenuButton;

	UPROPERTY(EditAnywhere, Category = "Class Type")
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UMainMenuUI* MapMenuWidget;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnResumeButtonClick();

	UFUNCTION(BlueprintImplementableEvent)
	void OnMapSelectionButtonClick();

	UFUNCTION(BlueprintImplementableEvent)
	void OnMenuButtonClick();
};

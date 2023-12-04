// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MapSelectionUI.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESONE_API UMapSelectionUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MapsGone = 0;

	// Widgets Binding
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClockLandButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* HomeMapButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* LeftButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* RightButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* SkyIslandButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LevelName;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClockLandButtonClick();

	UFUNCTION()
	void OnHomeMapButtonClick();

	UFUNCTION()
	void OnSkyIslandButtonClick();

	UFUNCTION()
	void OnBackButtonClick();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLeftButtonClick();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnRightButtonClick();

	UFUNCTION(BlueprintCallable)
	void SetLevelName(FText Name);

	UPROPERTY(EditAnywhere, Category = "Class Type")
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UMainMenuUI* MainMenuWidget;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "MapSelectionUI.h"
#include "MainMenuUI.h"
#include "ItTakesOne/Controllers/MainMenuPlayerController.h"
#include "ItTakesOne/Data/SaveGames/ContentSaveGame.h"
#include "ItTakesOne/Framework/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void UMapSelectionUI::NativeConstruct()
{
	if (ClockLandButton) ClockLandButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnClockLandButtonClick);
	if (SkyIslandButton) SkyIslandButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnSkyIslandButtonClick);
	if (HomeMapButton) HomeMapButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnHomeMapButtonClick);
	if (BackButton) BackButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnBackButtonClick);
	if (LeftButton) LeftButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnLeftButtonClick);
	if (RightButton) RightButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnRightButtonClick);
}

void UMapSelectionUI::HideText() 
{
	SetLockText(FText::FromString(""));
}

void UMapSelectionUI::OnClockLandButtonClick()
{
	const auto GameInstance = GetGameInstance<UMainGameInstance>();
	const auto ContentData = GameInstance->GetContentData();

	if (ContentData->Home.bPlaythroughComplete)
	{
		UGameplayStatics::OpenLevel(this, FName("ClockLand"));
	}
	else
	{
		if (LockedText)
		{
			SetLockText(FText::FromString("Level Not Yet Unlocked!"));
			GetWorld()->GetTimerManager().SetTimer(LockTimerHandle, this, &UMapSelectionUI::HideText, ShowTime, false);
		}
	}
}

void UMapSelectionUI::OnHomeMapButtonClick()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("home clicked"));

	UGameplayStatics::OpenLevel(this, FName("Home"));
}

void UMapSelectionUI::OnSkyIslandButtonClick()
{
	const auto GameInstance = GetGameInstance<UMainGameInstance>();
	const auto ContentData = GameInstance->GetContentData();

	if (ContentData->Home.bPlaythroughComplete)
	{
		UGameplayStatics::OpenLevel(this, FName("SkyIsland"));
	}
	else
	{
		if (LockedText)
		{
			SetLockText(FText::FromString("Level Not Yet Unlocked!"));
			GetWorld()->GetTimerManager().SetTimer(LockTimerHandle, this, &UMapSelectionUI::HideText, ShowTime, false);
		}
	}
}

void UMapSelectionUI::OnBackButtonClick()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("back clicked"));

	RemoveFromParent();

	if (MenuWidgetClass)
	{
		AMainMenuPlayerController* Controller = Cast<AMainMenuPlayerController>(GetWorld()->GetFirstPlayerController());
		if (Controller)
		{
			MainMenuWidget = CreateWidget<UMainMenuUI>(Controller, MenuWidgetClass);

			if (MainMenuWidget)
			{
				MainMenuWidget->AddToPlayerScreen();
			}
		}
	}
}

void UMapSelectionUI::SetLevelName(FText Name)
{
	if (LevelName) LevelName->SetText(Name);
}

void UMapSelectionUI::SetLockText(FText Name)
{
	if (LockedText) LockedText->SetText(Name);
}

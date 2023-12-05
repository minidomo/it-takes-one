// Fill out your copyright notice in the Description page of Project Settings.


#include "MapSelectionUI.h"
#include "MainMenuUI.h"
#include "ItTakesOne/Controllers/MainMenuPlayerController.h"
#include "ItTakesOne/Data/SaveGames/ContentSaveGame.h"
#include "ItTakesOne/Framework/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UMapSelectionUI::NativeConstruct()
{
	const auto GameInstance = GetGameInstance<UMainGameInstance>();
	const auto ContentData = GameInstance->GetContentData();

	if (ClockLandButton)
	{
		if (ContentData->Home.bPlaythroughComplete)
		{
			ClockLandButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnClockLandButtonClick);
		}
		else
		{
			ClockLandButton->SetIsEnabled(false);
		}
	}

	if (SkyIslandButton)
	{
		if (ContentData->ClockLand.bPlaythroughComplete)
		{
			SkyIslandButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnSkyIslandButtonClick);
		}
		else
		{
			SkyIslandButton->SetIsEnabled(false);
		}
	}

	if (HomeMapButton) HomeMapButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnHomeMapButtonClick);
	if (BackButton) BackButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnBackButtonClick);
	if (LeftButton) LeftButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnLeftButtonClick);
	if (RightButton) RightButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnRightButtonClick);
}

void UMapSelectionUI::OnClockLandButtonClick()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("clock clicked"));

	UGameplayStatics::OpenLevel(this, FName("ClockLand"));
}

void UMapSelectionUI::OnHomeMapButtonClick()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("home clicked"));

	UGameplayStatics::OpenLevel(this, FName("Home"));
}

void UMapSelectionUI::OnSkyIslandButtonClick()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("sky clicked"));

	UGameplayStatics::OpenLevel(this, FName("SkyIsland"));
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

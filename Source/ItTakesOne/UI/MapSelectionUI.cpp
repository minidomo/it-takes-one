// Fill out your copyright notice in the Description page of Project Settings.


#include "MapSelectionUI.h"
#include "MainMenuUI.h"
#include "ItTakesOne/Controllers/MainMenuPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UMapSelectionUI::NativeConstruct()
{
	if (ClockLandButton) ClockLandButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnClockLandButtonClick);
	if (HomeMapButton) HomeMapButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnHomeMapButtonClick);
	if (SkyIslandButton) SkyIslandButton->OnClicked.AddDynamic(this, &UMapSelectionUI::OnSkyIslandButtonClick);
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

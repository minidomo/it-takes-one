// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuGameMode.h"

#include "Blueprint/UserWidget.h"
#include "ItTakesOne/MainMenuPlayerController.h"
#include "ItTakesOne/MainMenuUI.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/Blueprints/BP_MainMenuPlayerController"));
	if (PlayerControllerBPClass.Class)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

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

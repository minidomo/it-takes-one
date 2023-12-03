// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerDeathMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPlayerDeathMenu::NativeConstruct()
{
	Super::NativeConstruct();

	MainMenuButton->OnClicked.AddDynamic(this, &UPlayerDeathMenu::OnMainMenuButtonClick);
	RestartButton->OnClicked.AddDynamic(this, &UPlayerDeathMenu::OnRestartButtonClick);
}

void UPlayerDeathMenu::OnMainMenuButtonClick()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}

void UPlayerDeathMenu::OnRestartButtonClick()
{
	UGameplayStatics::OpenLevel(this, "SkyIsland");
}

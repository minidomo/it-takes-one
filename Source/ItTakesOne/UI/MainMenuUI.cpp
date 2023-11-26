// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUI.h"
#include "MapSelectionUI.h"
#include "ItTakesOne/Controllers/MainMenuPlayerController.h"

void UMainMenuUI::NativeConstruct()
{
    if (StartButton) StartButton->OnClicked.AddDynamic(this, &UMainMenuUI::OnStartButtonClick);
    if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UMainMenuUI::OnQuitButtonClick);
}

void UMainMenuUI::OnStartButtonClick()
{
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("start clicked"));
    RemoveFromParent();

    if (MenuWidgetClass)
    {
        AMainMenuPlayerController *Controller = Cast<AMainMenuPlayerController>(GetWorld()->GetFirstPlayerController());
        if (Controller)
        {
            UMapSelectionUI* MapMenu = CreateWidget<UMapSelectionUI>(Controller, MenuWidgetClass);

            if (MapMenu)
            {
                MapMenu->AddToPlayerScreen();
            }
        }
    }
    
}

void UMainMenuUI::OnQuitButtonClick()
{
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("quit clicked"));

    APlayerController* PlayerController = GetOwningPlayer();
    if (PlayerController)
    {
        // Execute the "Quit" console command
        PlayerController->ConsoleCommand("Quit");
    }
}
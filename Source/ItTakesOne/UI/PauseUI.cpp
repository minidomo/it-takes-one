// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseUI.h"

void UPauseUI::NativeConstruct()
{
    if (ResumeButton) ResumeButton->OnClicked.AddDynamic(this, &UPauseUI::OnResumeButtonClick);
    if (MapSelectionButton) MapSelectionButton->OnClicked.AddDynamic(this, &UPauseUI::OnMapSelectionButtonClick);
    if (MenuButton) MenuButton->OnClicked.AddDynamic(this, &UPauseUI::OnMenuButtonClick);
}


// void UPauseUI::OnMapSelectionButtonClick()
// {
//     RemoveFromParent();

//     if (MenuWidgetClass)
//     {
//         AMainMenuPlayerController *Controller = Cast<AMainMenuPlayerController>(GetWorld()->GetFirstPlayerController());
//         if (Controller)
//         {
//             UMapSelectionUI* MapMenu = CreateWidget<UMapSelectionUI>(Controller, MenuWidgetClass);

//             if (MapMenu)
//             {
//                 MapMenu->AddToPlayerScreen();
//             }
//         }
//     }
// }

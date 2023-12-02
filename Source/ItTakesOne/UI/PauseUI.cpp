// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseUI.h"

void UPauseUI::NativeConstruct()
{
    if (ResumeButton) ResumeButton->OnClicked.AddDynamic(this, &UPauseUI::OnResumeButtonClick);
    if (MenuButton) MenuButton->OnClicked.AddDynamic(this, &UPauseUI::OnMenuButtonClick);
}

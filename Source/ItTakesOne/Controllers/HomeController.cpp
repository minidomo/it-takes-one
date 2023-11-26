// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeController.h"

AHomeController::AHomeController() {

}

void AHomeController::SetupInputComponent() {
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
        EnhancedInputComponent->BindAction(HammerAction, ETriggerEvent::Triggered, this, &AHomeController::OnHammerPressed);
    }
}

void AHomeController::OnHammerPressed() 
{
    AItTakesOneCharacter* character = Cast<AItTakesOneCharacter>(this->GetCharacter());
    if (character) {
        character->HammerEvent();
    }
}
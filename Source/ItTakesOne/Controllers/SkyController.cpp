// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyController.h"

ASkyController::ASkyController()
{

}

void ASkyController::SetupInputComponent() {
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
        EnhancedInputComponent->BindAction(JetAction, ETriggerEvent::Triggered, this, &ASkyController::OnJetHold);
        EnhancedInputComponent->BindAction(GliderAction, ETriggerEvent::Triggered, this, &ASkyController::OnGliderPressed);
    }
}

void ASkyController::OnJetHold()
{
    AItTakesOneCharacter* character = Cast<AItTakesOneCharacter>(this->GetCharacter());
    if (character) {
        character->JetEvent();
    }
}

void ASkyController::OnGliderPressed()
{
    AItTakesOneCharacter* character = Cast<AItTakesOneCharacter>(this->GetCharacter());
    if (character) {
        character->GliderEvent();
    }
}
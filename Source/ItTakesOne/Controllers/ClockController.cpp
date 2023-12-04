// Fill out your copyright notice in the Description page of Project Settings.


#include "ClockController.h"

AClockController::AClockController() {

}

void AClockController::SetupInputComponent() {
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
        EnhancedInputComponent->BindAction(ClockAction, ETriggerEvent::Triggered, this, &AClockController::OnClockPressed);
    }
}

void AClockController::OnClockPressed() 
{
    AItTakesOneCharacter* character = Cast<AItTakesOneCharacter>(this->GetCharacter());
    if (character) {
        character->ClockEvent();
    }
}
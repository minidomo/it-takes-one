// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"


ABasePlayerController::ABasePlayerController() {

}

void ABasePlayerController::BeginPlay() {
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ABasePlayerController::SetupInputComponent() {
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABasePlayerController::OnMovePressed);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABasePlayerController::OnJumpPressed);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABasePlayerController::OnLook);
        EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ABasePlayerController::OnDashPressed);
        EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ABasePlayerController::OnPausePressed);
    }
}

void ABasePlayerController::OnMovePressed(const FInputActionValue& Value) {
    AItTakesOneCharacter* character = Cast<AItTakesOneCharacter>(this->GetCharacter());
    if (character) {
        character->MoveEvent(Value);
    }
}

void ABasePlayerController::OnLook(const FInputActionValue& Value) {
    AItTakesOneCharacter* character = Cast<AItTakesOneCharacter>(this->GetCharacter());
    if (character) {
        character->LookEvent(Value);
    }
}

void ABasePlayerController::OnJumpPressed() {
    AItTakesOneCharacter* character = Cast<AItTakesOneCharacter>(this->GetCharacter());
    if (character) {
        character->JumpEvent();
    }
}

void ABasePlayerController::OnDashPressed() {
    AItTakesOneCharacter* character = Cast<AItTakesOneCharacter>(this->GetCharacter());
    if (character) {
        character->DashEvent();
    }
}

void ABasePlayerController::OnPausePressed() {
    AItTakesOneCharacter* character = Cast<AItTakesOneCharacter>(this->GetCharacter());
    if (character) {
        character->PauseEvent();
    }
}


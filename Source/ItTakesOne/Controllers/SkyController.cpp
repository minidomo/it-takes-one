// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyController.h"

#include "Blueprint/UserWidget.h"
#include "ItTakesOne/Actors/PlayerStates/SkyPlayerState.h"

ASkyController::ASkyController()
{
}

void ASkyController::BeginPlay()
{
	Super::BeginPlay();

	if (const auto CurPlayerState = GetPlayerState<ASkyPlayerState>())
	{
		CurPlayerState->OnHealthUpdateDelegate.AddDynamic(this, &ASkyController::OnHealthUpdate);
	}

	InitGui();
}

void ASkyController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(JetAction, ETriggerEvent::Triggered, this, &ASkyController::OnJetHold);
		EnhancedInputComponent->BindAction(GliderAction, ETriggerEvent::Triggered, this,
		                                   &ASkyController::OnGliderPressed);
	}
}

void ASkyController::InitGui()
{
	if (*PlayerHudClass)
	{
		PlayerHudWidget = CreateWidget(this, PlayerHudClass);
		if (PlayerHudWidget)
		{
			PlayerHudWidget->AddToViewport();
		}
	}

	if (*PlayerDeathMenuClass)
	{
		PlayerDeathMenuWidget = CreateWidget(this, PlayerDeathMenuClass);
	}
}

void ASkyController::OnJetHold()
{
	AItTakesOneCharacter* character = Cast<AItTakesOneCharacter>(this->GetCharacter());
	if (character)
	{
		character->JetEvent();
	}
}

void ASkyController::OnGliderPressed()
{
	AItTakesOneCharacter* character = Cast<AItTakesOneCharacter>(this->GetCharacter());
	if (character)
	{
		character->GliderEvent();
	}
}

void ASkyController::OnHealthUpdate(float OldHealth, float NewHealth)
{
	if (FMath::IsNearlyZero(NewHealth))
	{
		GetCharacter()->Destroy();
		SetShowMouseCursor(true);
		if (PlayerDeathMenuWidget)
		{
			PlayerDeathMenuWidget->AddToViewport();
		}
	}
}

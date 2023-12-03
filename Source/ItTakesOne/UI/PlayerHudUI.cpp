// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHudUI.h"

#include "HealthBarUI.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "ItTakesOne/Actors/Characters/WindBossCharacter.h"
#include "ItTakesOne/Actors/PlayerStates/SkyPlayerState.h"
#include "Kismet/GameplayStatics.h"

void UPlayerHudUI::OnPlayerHealthUpdate(float OldHealth, float NewHealth)
{
	const float Percent = NewHealth / SkyPlayerState->GetMaxHealth();;
	PlayerHealthBar->GetProgressBar()->SetPercent(Percent);
}

void UPlayerHudUI::OnBossHealthUpdate(float OldHealth, float NewHealth)
{
	const float Percent = NewHealth / WindBossCharacter->GetMaxHealth();;
	BossHealthBar->GetProgressBar()->SetPercent(Percent);

	if (FMath::IsNearlyZero(NewHealth))
	{
		BossName->SetVisibility(ESlateVisibility::Hidden);
		BossHealthBar->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPlayerHudUI::NativeConstruct()
{
	Super::NativeConstruct();

	SkyPlayerState = Cast<ASkyPlayerState>(UGameplayStatics::GetActorOfClass(this, ASkyPlayerState::StaticClass()));
	WindBossCharacter = Cast<AWindBossCharacter>(
		UGameplayStatics::GetActorOfClass(this, AWindBossCharacter::StaticClass()));

	if (SkyPlayerState)
	{
		const float HealthPercent = SkyPlayerState->GetHealth() / SkyPlayerState->GetMaxHealth();
		PlayerHealthBar->GetProgressBar()->SetPercent(HealthPercent);

		SkyPlayerState->OnHealthUpdateDelegate.AddDynamic(this, &UPlayerHudUI::OnPlayerHealthUpdate);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: could not find player state"), *GetName());
	}

	if (WindBossCharacter)
	{
		BossName->SetText(FText::FromString(WindBossCharacter->GetBossName()));

		const float HealthPercent = WindBossCharacter->GetHealth() / WindBossCharacter->GetMaxHealth();
		BossHealthBar->GetProgressBar()->SetPercent(HealthPercent);

		WindBossCharacter->OnHealthUpdateDelegate.AddDynamic(this, &UPlayerHudUI::OnBossHealthUpdate);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: could not find boss character"), *GetName());
	}
}

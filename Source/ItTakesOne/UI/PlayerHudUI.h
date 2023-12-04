// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHudUI.generated.h"

class UProgressBar;
class AWindBossCharacter;
class ASkyPlayerState;
class UTextBlock;

UCLASS()
class ITTAKESONE_API UPlayerHudUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UProgressBar* PlayerHealthBar;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UProgressBar* BossHealthBar;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* BossName;

	UPROPERTY()
	ASkyPlayerState* SkyPlayerState;

	UPROPERTY()
	AWindBossCharacter* WindBossCharacter;

	UFUNCTION()
	void OnPlayerHealthUpdate(float OldHealth, float NewHealth);

	UFUNCTION()
	void OnBossHealthUpdate(float OldHealth, float NewHealth);

	void HideBossGui();

protected:
	virtual void NativeConstruct() override;
};

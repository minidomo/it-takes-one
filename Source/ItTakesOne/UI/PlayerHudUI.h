// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHudUI.generated.h"

class AWindBossCharacter;
class ASkyPlayerState;
class UTextBlock;
class UHealthBarUI;

UCLASS()
class ITTAKESONE_API UPlayerHudUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UHealthBarUI* PlayerHealthBar;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UHealthBarUI* BossHealthBar;

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

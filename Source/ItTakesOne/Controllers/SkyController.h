// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "SkyController.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESONE_API ASkyController : public ABasePlayerController
{
	GENERATED_BODY()

public:
	ASkyController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JetAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* GliderAction;

protected:
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> PlayerHudClass;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> PlayerDeathMenuClass;

	UPROPERTY()
	UUserWidget* PlayerHudWidget;

	UPROPERTY()
	UUserWidget* PlayerDeathMenuWidget;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void OnJetHold();
	void OnGlideHold();
	void OnGlideEnd();

	UFUNCTION()
	void OnHealthUpdate(float OldHealth, float NewHealth);

	void InitGui();
};

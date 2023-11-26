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
    virtual void SetupInputComponent() override;

	void OnJetHold();
	void OnGliderPressed();
};

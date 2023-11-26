// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "HomeController.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESONE_API AHomeController : public ABasePlayerController
{
	GENERATED_BODY()
	
public: 
	AHomeController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* HammerAction;

protected:
    virtual void SetupInputComponent() override;

	void OnHammerPressed();
};

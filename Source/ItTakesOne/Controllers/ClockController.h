// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "ClockController.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESONE_API AClockController : public ABasePlayerController
{
	GENERATED_BODY()
	
public:
	AClockController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* ClockAction;

protected:
    virtual void SetupInputComponent() override;

	void OnClockPressed();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AItTakesOneCharacter;

UCLASS()
class ITTAKESONE_API UMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMainCharacterAnimInstance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AItTakesOneCharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float GroundSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bMoving;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIdle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bFalling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bDash;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHammer;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};

﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "ItTakesOne/ItTakesOneCharacter.h"

UMainCharacterAnimInstance::UMainCharacterAnimInstance()
{
}

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AItTakesOneCharacter>(GetOwningActor());
	if (Character)
	{
		CharacterMovement = Character->GetCharacterMovement();
	}
}

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValid(Character)) { return; }

	Velocity = CharacterMovement->Velocity;
	GroundSpeed = FVector(Velocity.X, Velocity.Y, 0).Length();

	TArray Statuses = {
		bMoving = Character->IsMoving(),
		bDash = Character->IsDash(),
		bHammer = Character->IsHammer(),
		bJet = Character->IsJet(),
		bGlide = Character->IsGlide(),
		bJump = Character->IsJump(),
		bFallingZ = Character->IsFallingZ(),
	};

	bIdle = true;
	for (const auto& Status : Statuses)
	{
		bIdle &= !Status;
	}
}

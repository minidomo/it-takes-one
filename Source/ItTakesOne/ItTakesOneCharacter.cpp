// Copyright Epic Games, Inc. All Rights Reserved.

#include "ItTakesOneCharacter.h"
#include "Actors/BreakableActor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/GameEngine.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Actors/GameModes/PlayableGameModeBase.h"
#include "Actors/HomeMap/TriggerActor.h"

//////////////////////////////////////////////////////////////////////////
// AItTakesOneCharacter

AItTakesOneCharacter::AItTakesOneCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}


void AItTakesOneCharacter::Destroyed()
{
	// store copy of controller since Super::Destroyed unpossesses the controller 
	AController* ControllerCopy = GetController();
	Super::Destroyed();

	if (const auto GameMode = GetWorld()->GetAuthGameMode<APlayableGameModeBase>())
	{
		GameMode->OnPlayerDiedDelegate.Broadcast(this, ControllerCopy);
	}
}

void AItTakesOneCharacter::MoveEvent(const FInputActionValue& Value)
{
	if (CanPerformAction(ECharacterActionStateEnum::MOVE)) {
		// input is a Vector2D
		FVector2D MovementVector = Value.Get<FVector2D>();

		if (Controller != nullptr)
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			// get right vector
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// add movement
			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);

			UpdateActionState(ECharacterActionStateEnum::MOVE);
			GetWorldTimerManager().SetTimer(HammerTimerHandle, this, &AItTakesOneCharacter::ResetAction, 0.01f, false);
		}
	}
	
}

void AItTakesOneCharacter::LookEvent(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AItTakesOneCharacter::HammerEvent()
{
	if (CanPerformAction(ECharacterActionStateEnum::HAMMER)) {
		IsHammer = true;
		AttachEvent();
		UpdateActionState(ECharacterActionStateEnum::HAMMER);
		if (Controller != nullptr)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Use Hammer"));
			}

			// Destory the BreakableActor if the Character overlap with the collision box of the breakableactor
			// Array to hold all overlapping actors
			TArray<AActor*> OverlappingActors;

			// Get all actors that the character is currently overlapping
			GetOverlappingActors(OverlappingActors);

			// Loop through each actor
			for (AActor* Actor : OverlappingActors)
			{
				if (Actor->IsA(ABreakableActor::StaticClass())) {
					// Check if the actor is of the BreakableActor class
					ABreakableActor* BreakableActor = Cast<ABreakableActor>(Actor);
					if (BreakableActor != nullptr)
					{
						BreakableActor->Destroy();
					}
				}

				if (Actor->IsA(ATriggerActor::StaticClass())) {
					ATriggerActor* tactor = Cast<ATriggerActor>(Actor);
					tactor->OnTriggerDelegate.Broadcast();
					tactor->Destroy();
				}
			}
		}
		GetWorldTimerManager().SetTimer(HammerTimerHandle, this, &AItTakesOneCharacter::ResetAction, 2.5f, false);
	}
}

void AItTakesOneCharacter::ResetAction() {

	UpdateActionState(ECharacterActionStateEnum::IDLE);

	if (IsHammer) {
		DetachEvent();
		IsHammer = false;
	} 
}

void AItTakesOneCharacter::StartPositionRecording() {

	GetWorld()->GetTimerManager().SetTimer(PositionHistoryTimerHandle, this, &AItTakesOneCharacter::UpdatePositionHistory, 0.2f, true);
	
}

void AItTakesOneCharacter::UpdatePositionHistory()
{
	// Add the current position to the history array
	PositionHistory.Add(GetActorLocation());

	// Optional: limit the size of the array to keep only the last 30 positions (3 seconds at 0.1 second intervals)
	if (PositionHistory.Num() > 15)
	{
		PositionHistory.RemoveAt(0);
	}

	PlaceFootstepDecals();
}

void AItTakesOneCharacter::PlaceFootstepDecals()
{
		float HalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		FVector FloorPosition = GetActorLocation() - FVector(0.0f, 0.0f, HalfHeight);
		FVector DecalPosition = FloorPosition + FVector(0.0f, 0.0f, 0.0f);
		UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), FootstepDecalMaterial, DecalSize, DecalPosition, FRotator(0.f, 0.f, 0.f), 3.0f);

		if (Decal)
		{
			Decal->SetFadeScreenSize(0.0001f);
		}
}

void AItTakesOneCharacter::ClockEvent()
{

	if (Controller != nullptr)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Use Clock!"));
		}

		if (PositionHistory.Num() >= 15)
		{
			// Move the character to the position from 3 seconds ago
			SetActorLocation(PositionHistory[0]);
		}
		
	}
}

bool AItTakesOneCharacter::CanPerformAction(ECharacterActionStateEnum UpdatedAction)
{
	switch (CharacterActionState)
	{
		case ECharacterActionStateEnum::IDLE:
		return true;
		break;
		case ECharacterActionStateEnum::MOVE:
		if (UpdatedAction != ECharacterActionStateEnum::HAMMER)
			return true;
		break;
		case ECharacterActionStateEnum::JUMP:
		if (UpdatedAction == ECharacterActionStateEnum::IDLE ||
			UpdatedAction == ECharacterActionStateEnum::MOVE)
			return true;
		break;
		case ECharacterActionStateEnum::DASH:
		if (UpdatedAction == ECharacterActionStateEnum::IDLE ||
			UpdatedAction == ECharacterActionStateEnum::MOVE)
			return true;
		case ECharacterActionStateEnum::HAMMER:
		return false;
		break;
	}

    return false;
}

void AItTakesOneCharacter::UpdateActionState(ECharacterActionStateEnum NewAction)
{
	if (NewAction == ECharacterActionStateEnum::MOVE || NewAction == ECharacterActionStateEnum::IDLE)
	{
		if(GetVelocity().Size() <= 0.1f)
		{
			CharacterActionState = ECharacterActionStateEnum::IDLE;
		} else
		{
			CharacterActionState = ECharacterActionStateEnum::MOVE;
		}
	}
	
	CharacterActionState = NewAction;
}

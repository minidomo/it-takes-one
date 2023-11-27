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
#include "Actors/GameModes/PlayableGameModeBase.h"

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
			// Check if the actor is of the BreakableActor class
			ABreakableActor* BreakableActor = Cast<ABreakableActor>(Actor);
			if (BreakableActor != nullptr)
			{
				// Destroy the BreakableActor
				BreakableActor->Destroy();
			}
		}
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

	for (FVector Position : PositionHistory)
	{
		UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), FootstepDecalMaterial, DecalSize, Position, FRotator(0.f, 0.f, 0.f), 10.0f);
		

		if (Decal)
		{
			Decal->SetFadeScreenSize(0.0001f);
		}
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
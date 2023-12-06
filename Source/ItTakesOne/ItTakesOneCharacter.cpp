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

	GlideGravityScale = .1;
	GetCharacterMovement()->GravityScale = 1.75;
	DashMagnitude = 1000.f;
	DashAnimationTime = .5f;
	HammerAnimationTime = 3.35f;
	DestroyAnimationTime = 1.4f;
	JetMagnitude = 100.f;
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

void AItTakesOneCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bJet)
	{
		bJet = !IsFallingZ();
	}

	if (bJump)
	{
		bJump = !IsFallingZ();
	}
}

void AItTakesOneCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	bJet = bGlide = bJump = false;
}

void AItTakesOneCharacter::MoveEvent(const FInputActionValue& Value)
{
	if (bHammer) { return; }

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

void AItTakesOneCharacter::JumpEvent()
{
	if (!FMath::IsNearlyZero(GetCharacterMovement()->Velocity.Z) || bHammer) { return; }

	bJump = true;
	Jump();
}

void AItTakesOneCharacter::DashEvent()
{
	if (bHammer || !DashAvailable || !IsMoving() || bJet || bGlide) { return; }

	DashAvailable = false;
	bDash = true;
	FVector DashVelocity = GetActorForwardVector() * DashMagnitude;
	LaunchCharacter(DashVelocity, false, false);

	// needs to be different timers because using SetTimer on a timer that is currently being used will result in the
	// first one getting cleared
	GetWorldTimerManager().SetTimer(DashTimerHandle, [&] { bDash = false; }, DashAnimationTime, false);
	GetWorldTimerManager().SetTimer(DashCoolDownHandle, [&] { DashAvailable = true; }, DashCoolDown, false);
}

void AItTakesOneCharacter::HammerEvent()
{
	if (!GetCharacterMovement()->Velocity.IsZero() || bDash || bHammer) { return; }

	bHammer = true;
	AttachEvent();

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
		if (Actor->IsA(ABreakableActor::StaticClass()))
		{
			// Check if the actor is of the BreakableActor class
			ABreakableActor* BreakableActor = Cast<ABreakableActor>(Actor);
			GetWorldTimerManager().SetTimer(DestroyTimerHandle, [BreakableActor]()
			{
				BreakableActor->Destroy();
			}, DestroyAnimationTime, false);

			// destroy the first one found, so break afterwards
			break;
		}

		if (Actor->IsA(ATriggerActor::StaticClass()))
		{
			ATriggerActor* TActor = Cast<ATriggerActor>(Actor);
			TActor->OnTriggerDelegate.Broadcast();
			GetWorldTimerManager().SetTimer(DestroyTimerHandle, [TActor]()
			{
				TActor->Destroy();
			}, DestroyAnimationTime, false);

			// destroy the first one found, so break afterwards
			break;
		}
	}

	GetWorldTimerManager().SetTimer(HammerTimerHandle, [&]
	{
		DetachEvent();
		bHammer = false;
	}, HammerAnimationTime, false);
}

void AItTakesOneCharacter::JetEvent()
{
	bJet = true;
	LaunchCharacter(FVector(0, 0, JetMagnitude), false, false);
}

void AItTakesOneCharacter::GlideHoldEvent()
{
	if (IsFallingZ())
	{
		bGlide = true;
		GetCharacterMovement()->GravityScale = GlideGravityScale;
	}
	else
	{
		GetCharacterMovement()->GravityScale = InitialGravityScale;
	}
}

void AItTakesOneCharacter::GlideEndEvent()
{
	bGlide = false;
	GetCharacterMovement()->GravityScale = InitialGravityScale;
}

void AItTakesOneCharacter::StartPositionRecording()
{
	GetWorld()->GetTimerManager().SetTimer(PositionHistoryTimerHandle, this,
	                                       &AItTakesOneCharacter::UpdatePositionHistory, 0.2f, true);
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

void AItTakesOneCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitialGravityScale = GetCharacterMovement()->GravityScale;
}

void AItTakesOneCharacter::PlaceFootstepDecals()
{
	float HalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FVector FloorPosition = GetActorLocation() - FVector(0.0f, 0.0f, HalfHeight);
	FVector DecalPosition = FloorPosition + FVector(0.0f, 0.0f, 0.0f);
	UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), FootstepDecalMaterial, DecalSize,
	                                                                DecalPosition, FRotator(0.f, 0.f, 0.f), 3.0f);

	if (Decal)
	{
		Decal->SetFadeScreenSize(0.0001f);
	}
}

bool AItTakesOneCharacter::IsFallingZ()
{
	return GetCharacterMovement()->Velocity.Z < 0;
}

bool AItTakesOneCharacter::IsMoving()
{
	const FVector Velocity = GetCharacterMovement()->Velocity;
	const float GroundSpeed = FVector(Velocity.X, Velocity.Y, 0).Length();
	return !GetCharacterMovement()->GetCurrentAcceleration().IsZero() && GroundSpeed > 3.f;
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

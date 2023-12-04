// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ItTakesOneCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterActionStateEnum : uint8 {
	IDLE UMETA(DisplayName = "Idling"),
	MOVE UMETA(DisplayName = "Moving"),
	DASH UMETA(DisplayName = "Dashing"),
	JUMP UMETA(DisplayName = "Jumping"),
	HAMMER UMETA(DisplayName = "Hammering")
};

UCLASS(config=Game)
class AItTakesOneCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AItTakesOneCharacter();

	void MoveEvent(const FInputActionValue& Value);
	void LookEvent(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void JumpEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void DashEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void PauseEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void JetEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void GliderEvent();

	UFUNCTION(BlueprintCallable)
	void StartPositionRecording();

	void HammerEvent();
	UFUNCTION(BlueprintImplementableEvent)
	void AttachEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void DetachEvent();

	void ResetAction();

	void ClockEvent();

	//place the footstep for the clock
	void PlaceFootstepDecals();

	UFUNCTION(BlueprintCallable)
	bool CanPerformAction(ECharacterActionStateEnum UpdatedAction);

	UFUNCTION(BlueprintCallable)
	void UpdateActionState(ECharacterActionStateEnum NewAction);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ECharacterActionStateEnum CharacterActionState;


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void Destroyed() override;

private: 
	FTimerHandle PositionHistoryTimerHandle;
	// Array to store positions
	TArray<FVector> PositionHistory;
	// Function to update position history
	void UpdatePositionHistory();

	FTimerHandle HammerTimerHandle;

	bool IsHammer = false;


protected:
	// Decal material for the footstep
	UPROPERTY(EditAnywhere, Category = "Footsteps")
		UMaterialInterface* FootstepDecalMaterial;

	// Decal size
	UPROPERTY(EditAnywhere, Category = "Footsteps")
		FVector DecalSize;
};

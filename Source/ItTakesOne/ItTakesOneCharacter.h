// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ItTakesOneCharacter.generated.h"

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

	void JumpEvent();

	void DashEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void PauseEvent();

	void JetEvent();

	void GlideHoldEvent();
	void GlideEndEvent();

	UFUNCTION(BlueprintCallable)
	void StartPositionRecording();

	void HammerEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void AttachEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void DetachEvent();

	void ClockEvent();

	//place the footstep for the clock
	void PlaceFootstepDecals();

	bool IsFallingZ();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool IsDash() const { return bDash; }
	FORCEINLINE bool IsHammer() const { return bHammer; }
	FORCEINLINE bool IsJet() const { return bJet; }
	FORCEINLINE bool IsGlide() const { return bGlide; }
	FORCEINLINE bool IsJump() const { return bJump; }

	bool IsMoving();

	virtual void Destroyed() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Landed(const FHitResult& Hit) override;

private:
	float InitialGravityScale;

	FTimerHandle PositionHistoryTimerHandle;
	// Array to store positions
	TArray<FVector> PositionHistory;
	// Function to update position history
	void UpdatePositionHistory();

	FTimerHandle HammerTimerHandle;
	FTimerHandle HammerCoolDownHandle;
	FTimerHandle DestroyTimerHandle;

	FTimerHandle DashTimerHandle;
	FTimerHandle DashCoolDownHandle;
	float DashCoolDown = 5.f;
	bool DashAvailable = true;

protected:
	// Decal material for the footstep
	UPROPERTY(EditAnywhere, Category = "Footsteps")
	UMaterialInterface* FootstepDecalMaterial;

	// Decal size
	UPROPERTY(EditAnywhere, Category = "Footsteps")
	FVector DecalSize;

	UPROPERTY(EditAnywhere, Category = Glide)
	float GlideGravityScale;

	UPROPERTY(EditAnywhere)
	float DashAnimationTime;

	UPROPERTY(EditAnywhere)
	float DashMagnitude;

	UPROPERTY(EditAnywhere)
	float HammerAnimationTime;

	UPROPERTY(EditAnywhere)
	float DestroyAnimationTime;

	UPROPERTY(EditAnywhere)
	float JetMagnitude;

	bool bHammer;
	bool bDash;
	bool bGlide;
	bool bJet;
	bool bJump;

	virtual void BeginPlay() override;
};

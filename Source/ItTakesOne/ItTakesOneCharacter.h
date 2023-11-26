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

	UFUNCTION(BlueprintImplementableEvent)
	void HammerEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void ClockEvent();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void Destroyed() override;
};

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

	// /** MappingContext */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	// class UInputMappingContext* DefaultMappingContext;

	// /** Jump Input Action */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	// class UInputAction* JumpAction;

	// /** Move Input Action */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	// class UInputAction* MoveAction;

	// /** Look Input Action */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	// class UInputAction* LookAction;

public:
	AItTakesOneCharacter();

	/** Called for movement input */
	void MoveEvent(const FInputActionValue& Value);

	/** Called for looking input */
	void LookEvent(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void JumpEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void DashEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void PauseEvent();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void Destroyed() override;
};

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Logging/LogMacros.h"

#include "Components/StaminaComponent.h"
#include "Components/HealthComponent.h"
#include "Components/HungerComponent.h"
#include "Components/ThirstComponent.h"
#include "Components/MovementStateComponent.h"

#include "ReclaimersCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AReclaimersCharacter : public ACharacter
{
	GENERATED_BODY()

	// Start of default UE5 Properties //

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	// End of default UE5 Properties //

	//////////////////////////////////////////////////////////////////////////
	// CHARACTER - HEALTH
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Status", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	//////////////////////////////////////////////////////////////////////////
	// CHARACTER - STAMINA
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Status", meta = (AllowPrivateAccess = "true"))
	UStaminaComponent* StaminaComponent;

	//////////////////////////////////////////////////////////////////////////
	// CHARACTER - HUNGER
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Status", meta = (AllowPrivateAccess = "true"))
	UHungerComponent* HungerComponent;

	//////////////////////////////////////////////////////////////////////////
	// CHARACTER - THIRST
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Status", meta = (AllowPrivateAccess = "true"))
	UThirstComponent* ThirstComponent;

	//////////////////////////////////////////////////////////////////////////
	// CHARACTER - MOVEMENT
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Movement", meta = (AllowPrivateAccess = "true"))
	UMovementStateComponent* MovementStateComponent;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	/** The current characters max walk speed (WALKING STATE) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Movement", meta = (AllowPrivateAccess = "true"))
	int WalkSpeed;

	/** The current characters max run speed (WALKING STATE) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Movement", meta = (AllowPrivateAccess = "true"))
	int RunSpeed;

	/** The current characters ambush speed multiplier */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Movement", meta = (AllowPrivateAccess = "true"))
	float AmbushSpeedMultiplier;


public: // Default public class functions by UE5 //
	AReclaimersCharacter();

public: // Default public class functions by UE5 //
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	

protected: // Default protected class items by UE5 //

	/** Called for movement input */
	FORCEINLINE void Move(const FInputActionValue& Value);

	/** Called for looking input */
	FORCEINLINE void Look(const FInputActionValue& Value);

	FORCEINLINE void Sprint(const FInputActionValue& Value);
	FORCEINLINE void StopSprinting();
	FORCEINLINE void ResetSprinting();

	// To add mapping context
	FORCEINLINE virtual void BeginPlay();

	FORCEINLINE virtual void Tick(float DeltaTime);

	// APawn interface
	FORCEINLINE virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
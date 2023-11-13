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

#include "ReclaimersCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);


UENUM(BlueprintType) // Make accessable in blueprints.
enum class EMovementState : uint8 {
	E_IDLE			UMETA(DisplayName = "IDLE"),	// Doing Nothing. Standing still.
	E_WALKING		UMETA(DisplayName = "WALKING"),	// Holding any movement key, such as W, A, D, S.
	E_RUNNING		UMETA(DisplayName = "RUNNING"),	// Holding any movement key whilst holding Shift.
	E_OTHER			UMETA(DisplayName = "OTHER")	// Any movement not implemented yet. (Such as flying, swimming, etc)
};

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

	/** The current movement state of the character (such as IDLE, RUNNING, WALKING etc) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Movement", meta = (AllowPrivateAccess = "true"))
	EMovementState MovementState;

	/** The current characters max walk speed (WALKING STATE) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Movement", meta = (AllowPrivateAccess = "true"))
	int WalkSpeed;

	/** The current characters max run speed (WALKING STATE) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Movement", meta = (AllowPrivateAccess = "true"))
	int RunSpeed;

	/** The current characters ambush speed multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Movement", meta = (AllowPrivateAccess = "true"))
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

	// To add mapping context
	FORCEINLINE virtual void BeginPlay();

	FORCEINLINE virtual void Tick(float DeltaTime);

	// APawn interface
	FORCEINLINE virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



protected:
	/** Sets the Characters current Health (Cannot exceed the maximum health) **/
	// FORCEINLINE virtual void SetHealth(float Value);

	/** Sets the Characters Max Health (Max - 1.000.000) **/
	// FORCEINLINE virtual void SetMaxHealth(float Value);

	/** Sets the Characters current MovementState **/
	FORCEINLINE virtual void SetMovementState(const EMovementState& Value);

public:
	/** Returns Characters current Health **/
	// FORCEINLINE float GetHealth() const { return Health; }

	/** Returns Characters Max Health **/
	// FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	/** Returns Characters current MovementState **/
	FORCEINLINE enum class EMovementState GetMovementState() const { return MovementState; }
};


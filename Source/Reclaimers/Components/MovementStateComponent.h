// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementStateComponent.generated.h"

UENUM(BlueprintType) // Make accessable in blueprints.
enum class EMovementState : uint8 {
	E_IDLE			UMETA(DisplayName = "IDLE"),	// Doing Nothing. Standing still.
	E_WALKING		UMETA(DisplayName = "WALKING"),	// Holding any movement key, such as W, A, D, S.
	E_RUNNING		UMETA(DisplayName = "RUNNING"),	// Holding any movement key whilst holding Shift.
	E_RESTING		UMETA(DisplayName = "RESTING"),	// Resting, disables all moving while in the resting state.
	E_OTHER			UMETA(DisplayName = "OTHER")	// Any movement not implemented yet. (Such as flying, swimming, etc)
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECLAIMERS_API UMovementStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementStateComponent();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetMovementState(const EMovementState& Value);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	EMovementState GetMovementState() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsIdle() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsResting() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsWalking() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsSprinting() const;

private:
	/** The current movement state of the character (such as IDLE, RUNNING, WALKING etc) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	EMovementState MovementState;

	/** Whether the character is currently sprinting. */
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	// bool bIsSprinting;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Reclaimers/ReclaimersCharacter.h>

DEFINE_LOG_CATEGORY(LogStaminaComponent);

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Stamina = 100.0f;
	MaxStamina = 100.0f;
	StaminaRecovery = 1.0f;		// TODO: Add Get/Set Methods
	StaminaDecay = 5.0f;		// TODO: Add Get/Set Methods

	// bIsSprinting = false;
}


// Called when the game starts
void UStaminaComponent::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get Character Owner
	AReclaimersCharacter* OwnerCharacter = Cast<AReclaimersCharacter>(GetOwner());
	if (OwnerCharacter)
	{
		// Stamina should only recharge / consume while the character is moving on ground.
		if (OwnerCharacter->GetCharacterMovement()->IsMovingOnGround()) {
			if (UMovementStateComponent* movementState = OwnerCharacter->GetMovementState()) {
				UStaminaComponent* StaminaComponent = OwnerCharacter->GetStaminaComponent();

				// If the character is running / sprinting, decrease / consume stamina.
				if (movementState->IsIdle()) {
					if (StaminaComponent->GetStamina() < StaminaComponent->GetMaxStamina()) {
						UE_LOG(LogStaminaComponent, Warning, TEXT("(IDLE) INCREASING STAMINA ..."));
						StaminaComponent->SetStamina(
							FMath::FInterpConstantTo(StaminaComponent->GetStamina(), StaminaComponent->GetMaxStamina(), DeltaTime, StaminaComponent->GetRecoveryRate())
						);
					}
				} // Increase Stamina by recharge rate 1x.
				else if (movementState->IsResting()) {
					if (StaminaComponent->GetStamina() < StaminaComponent->GetMaxStamina()) {
						UE_LOG(LogStaminaComponent, Warning, TEXT("(RESTING) INCREASING STAMINA ..."));
						StaminaComponent->SetStamina(
							FMath::FInterpConstantTo(StaminaComponent->GetStamina(), StaminaComponent->GetMaxStamina(), DeltaTime, (float)(StaminaComponent->GetRecoveryRate() * 2.5))
						);
					}
				} // Increase Stamina by recharge rate 2.5x
				else if (movementState->IsWalking()) {
					if (StaminaComponent->GetStamina() < StaminaComponent->GetMaxStamina()) {
						UE_LOG(LogStaminaComponent, Warning, TEXT("(WALKING) INCREASING STAMINA ..."));
						StaminaComponent->SetStamina(
							FMath::FInterpConstantTo(StaminaComponent->GetStamina(), StaminaComponent->GetMaxStamina(), DeltaTime, (float)(StaminaComponent->GetRecoveryRate() * .5))
						);
					}
				} // Increase Stamina by recharge rate 0.5x
				else if (movementState->IsRunning()) { // Decrease Stamina.
					if (StaminaComponent->GetStamina() > 0.0f) {
						UE_LOG(LogStaminaComponent, Warning, TEXT("DECREASING STAMINA ..."));
						StaminaComponent->SetStamina(
							FMath::FInterpConstantTo(StaminaComponent->GetStamina(), 0.0f, DeltaTime, StaminaComponent->GetDecayRate())
						);
					}
					else
					{
						// ResetSprinting();
					}
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// STAMINA

void UStaminaComponent::SetStamina(float NewStamina) {
	Stamina = FMath::Clamp(NewStamina, 0.0f, MaxStamina);

	// TODO: Disable Sprint at 0 Stamina
}

float UStaminaComponent::GetStamina() const { return Stamina; }

//////////////////////////////////////////////////////////////////////////
// MAX STAMINA

void UStaminaComponent::SetMaxStamina(float NewStamina) {
	MaxStamina = FMath::Clamp(NewStamina, 0.0f, 1000.0f);
}

float UStaminaComponent::GetMaxStamina() const { return MaxStamina; }

//////////////////////////////////////////////////////////////////////////
// RECOVERY & DECAY
float UStaminaComponent::GetRecoveryRate() const { return StaminaRecovery; }
float UStaminaComponent::GetDecayRate() const { return StaminaDecay; }

//////////////////////////////////////////////////////////////////////////
// SPRINTING

bool UStaminaComponent::CanSprint() const {
	if (Stamina > 0.0f) {
		return true;
	}

	return false;
}

// Is Sprinting
// bool UStaminaComponent::IsSprinting() const { return bIsSprinting; }
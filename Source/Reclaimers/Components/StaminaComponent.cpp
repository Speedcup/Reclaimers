// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"

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
void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) { Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }

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
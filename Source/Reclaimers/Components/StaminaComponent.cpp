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
	StaminaRecovery = 2.0f;
	StaminaDecay = 1.0f;
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
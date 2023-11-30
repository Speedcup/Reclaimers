// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100.0f;
	Health = 100.0f;
	HealthRegeneration = 2.0f;		// TODO: Add Get/Set Methods
}


// Called when the game starts
void UHealthComponent::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) { Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }

//////////////////////////////////////////////////////////////////////////
// HEALTH

void UHealthComponent::SetHealth(float NewHealth) {
	if (NewHealth > MaxHealth) return;

	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);

	if (NewHealth <= 0.0f) {
		DoPlayerDeath();
	}
}

float UHealthComponent::GetHealth() const {	return Health; }

//////////////////////////////////////////////////////////////////////////
// MAX HEALTH

void UHealthComponent::SetMaxHealth(float NewHealth) {
	MaxHealth = FMath::Clamp(NewHealth, 0.0f, 1000.0f);
}

float UHealthComponent::GetMaxHealth() const { return MaxHealth; }

//////////////////////////////////////////////////////////////////////////
// -
void UHealthComponent::DoPlayerDeath() {}
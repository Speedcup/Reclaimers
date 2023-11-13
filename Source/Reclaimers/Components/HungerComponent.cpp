// Fill out your copyright notice in the Description page of Project Settings.


#include "HungerComponent.h"

// Sets default values for this component's properties
UHungerComponent::UHungerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Hunger = 100.0f;
	MaxHunger = 100.0f;
	HungerDecay = 1.0f;		// TODO: Add Get/Set Methods
}


// Called when the game starts
void UHungerComponent::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void UHungerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) { Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }

//////////////////////////////////////////////////////////////////////////
// HUNGER

void UHungerComponent::SetHunger(float NewHunger) {
	Hunger = FMath::Clamp(NewHunger, 0.0f, MaxHunger);

	// TODO: Add damage every x ticks when hunger is 0.
	// Maybe do not remove food every tick? Just remove more food at certain ticks? Each 10 ticks e.g.?
	// It would be weird to damage the player every tick because he's starving so we should damage him each x ticks or change the starving method.
	// A: Remove Food on every Tick -> Damage players each 10 ticks when starving.
	// B: Remove Food each 10 Ticks -> Damage player whenever he is starving and the next food tick came.
}

float UHungerComponent::GetHunger() const { return Hunger; }

//////////////////////////////////////////////////////////////////////////
// MAX HUNGER

void UHungerComponent::SetMaxHunger(float NewMaxHunger) {
	MaxHunger = FMath::Clamp(NewMaxHunger, 0.0f, 1000.0f);
}

float UHungerComponent::GetMaxHunger() const { return MaxHunger; }
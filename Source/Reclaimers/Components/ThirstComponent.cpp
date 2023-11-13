// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirstComponent.h"

// Sets default values for this component's properties
UThirstComponent::UThirstComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Thirst = 100.0f;
	MaxThirst = 100.0f;
	ThirstDecay = 1.0f;
}

// Called when the game starts
void UThirstComponent::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void UThirstComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) { Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }


//////////////////////////////////////////////////////////////////////////
// THIRST

void UThirstComponent::SetThirst(float NewThirst) {
	Thirst = FMath::Clamp(NewThirst, 0.0f, MaxThirst);

	// TODO: Add damage every x ticks when thirst is 0.
	// Maybe do not remove thirst every tick? Just remove more thirst at certain ticks? Each 10 ticks e.g.?
	// It would be weird to damage the player every tick because he's dehydrating so we should damage him each x ticks or change the dehydration method.
	// A: Remove Thirst on every Tick -> Damage players each 10 ticks when dehydrating.
	// B: Remove Thirst each 10 Ticks -> Damage player whenever he is dehydrating and the next thirst tick came.
}

float UThirstComponent::GetThirst() const { return Thirst; }

//////////////////////////////////////////////////////////////////////////
// MAX THIRST

void UThirstComponent::SetMaxThirst(float NewMaxThirst) {
	MaxThirst = FMath::Clamp(NewMaxThirst, 0.0f, 1000.0f);
}

float UThirstComponent::GetMaxThirst() const { return MaxThirst; }
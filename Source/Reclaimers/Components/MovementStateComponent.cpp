// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementStateComponent.h"

// Sets default values for this component's properties
UMovementStateComponent::UMovementStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MovementState = EMovementState::E_IDLE;
	// bIsSprinting = false;
}


// Called when the game starts
void UMovementStateComponent::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void UMovementStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) { Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }

//////////////////////////////////////////////////////////////////////////
// MOVEMENT STATE
void UMovementStateComponent::SetMovementState(const EMovementState& Value) {
	MovementState = Value;
}

EMovementState UMovementStateComponent::GetMovementState() const { return MovementState; }

bool UMovementStateComponent::IsIdle() const { return (MovementState == EMovementState::E_IDLE); }
bool UMovementStateComponent::IsResting() const { return (MovementState == EMovementState::E_RESTING); }
bool UMovementStateComponent::IsWalking() const { return (MovementState == EMovementState::E_WALKING); }
bool UMovementStateComponent::IsRunning() const { return (MovementState == EMovementState::E_RUNNING); }
bool UMovementStateComponent::IsSprinting() const { return IsRunning(); }
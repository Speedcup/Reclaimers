// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECLAIMERS_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaminaComponent();

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void SetStamina(float NewStamina);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void SetMaxStamina(float Value);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	float GetMaxStamina() const;

private:
	/** The character's current stamina */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Status", meta = (AllowPrivateAccess = "true"))
	float Stamina;

	/** The character's current max stamina */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Status", meta = (AllowPrivateAccess = "true"))
	float MaxStamina;

	/** The character's current stamina recovery rate per (1) second */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Status", meta = (AllowPrivateAccess = "true"))
	float StaminaRecovery;

	/** The character's current stamina decay rate per (1) second */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Status", meta = (AllowPrivateAccess = "true"))
	float StaminaDecay;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};

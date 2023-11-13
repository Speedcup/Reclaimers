// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HungerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECLAIMERS_API UHungerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHungerComponent();

	UFUNCTION(BlueprintCallable, Category = "Hunger")
	void SetHunger(float NewHunger);

	UFUNCTION(BlueprintCallable, Category = "Hunger")
	float GetHunger() const;

	UFUNCTION(BlueprintCallable, Category = "Hunger")
	void SetMaxHunger(float Value);

	UFUNCTION(BlueprintCallable, Category = "Hunger")
	float GetMaxHunger() const;

private:
	/** The character's current hunger */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hunger", meta = (AllowPrivateAccess = "true"))
	float Hunger;

	/** The character's current max hunger */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hunger", meta = (AllowPrivateAccess = "true"))
	float MaxHunger;

	/** The character's current hunger decay */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hunger", meta = (AllowPrivateAccess = "true"))
	float HungerDecay;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
};

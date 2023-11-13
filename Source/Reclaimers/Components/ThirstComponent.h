// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThirstComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECLAIMERS_API UThirstComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UThirstComponent();

	UFUNCTION(BlueprintCallable, Category = "Thirst")
	void SetThirst(float NewThirst);

	UFUNCTION(BlueprintCallable, Category = "Thirst")
	float GetThirst() const;

	UFUNCTION(BlueprintCallable, Category = "Thirst")
	void SetMaxThirst(float NewMaxThirst);

	UFUNCTION(BlueprintCallable, Category = "Thirst")
	float GetMaxThirst() const;

private:
	/** The character's current thirst */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Status", meta = (AllowPrivateAccess = "true"))
	float Thirst;

	/** The character's current max thirst */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Status", meta = (AllowPrivateAccess = "true"))
	float MaxThirst;

	/** The character's current thirst decay */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Status", meta = (AllowPrivateAccess = "true"))
	float ThirstDecay;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};

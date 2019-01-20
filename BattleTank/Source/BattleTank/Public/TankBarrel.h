// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// void Elevate(float DegreesPerSecond);, hidecategories = ("Collision")
	// -1 is max downward speed, +1 is max upward speed
	void Elevate(float RelativeSpeed);
	
	
private:
	UPROPERTY(EditAnywhere, category = setup)
		float MaxDegreesPerSecond = 10; // Sensible Default

	UPROPERTY(EditAnywhere, category = setup)
		float MaxElevationDegrees = 40; 

	UPROPERTY(EditAnywhere, category = setup)
		float MinElevationDegrees = 0; 
	
};

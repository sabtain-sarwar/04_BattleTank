// Copyright Sabtain Sarwar

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
	UPROPERTY(EditDefaultsOnly, category = "setup")
		float MaxDegreesPerSecond = 10; // Sensible Default

	UPROPERTY(EditDefaultsOnly, category = "setup")
		float MaxElevationDegrees = 40; 

	UPROPERTY(EditDefaultsOnly, category = "setup")
		float MinElevationDegrees = 0; 
	
};

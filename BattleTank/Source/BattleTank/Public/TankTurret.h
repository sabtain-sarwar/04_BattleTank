// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	// -1 is max downward speed, +1 is max upward speed, hidecategories = ("Collision")
	void Rotate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, category = setup)
		float MaxDegreesPerSecond = 25; 
};

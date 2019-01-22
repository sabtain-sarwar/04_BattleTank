// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:
	// This is going to communicate the movement desire.It take in a float because it's going to  be between -1 and +1,and i'm
	// going to call that float Throw,which is the control throw,it's how far forward or back the control is moved.Video 151 and
	// read the blueprint
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveForward(float Throw);
	
};

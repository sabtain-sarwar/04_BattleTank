// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h" moved this include to TankAIController.cpp
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
protected:
	// Blueprint is a child class of the c++ class.So that's exactly what protected means,it means the children can read it.
	UPROPERTY(EditDefaultsOnly , Category = "Setup")
		float AcceptanceRadius = 8000; // 80 meters
	
private:
	virtual void Tick(float DeltaSeconds) override;
	//ATank* GetControlledTank() const;
	//ATank* GetPlayerTank() const; // returns a pointer to a playertank
	
	// How close the AI tank get to the player
	//float AcceptanceRadius = 1000;
};

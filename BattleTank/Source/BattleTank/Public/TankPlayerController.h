// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h" moved this include to TankPlayerController.cpp
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
private:
	ATank* GetControlledTank() const;

	// If we want to write (void BeginPlay()) we can, but we want to make sure we are overriding and adding to the functionality
	// that's further up the inheritance tree, because we want to make sure that all that other stuff that Unreal has written 
	// is also happening.So,the way you do that is using the keyword override.override says,please make sure there is something
	// else up the Inheritance tree with exactly the signature (BeginPlay()), precisely BeginPlay() with no parameters.That's 
	// what the override does,it checks that it can find this upward in the hierarchy. The keyword virtual says my Childrens are 
	// allowed to override or extend the functionality of this method.So,if the method was declared virtual,in the first place,
	// which this was in the case of BeginPlay() , it can be overridden by any ancestor in the future.Specifying virtual on an
	// already virtual method has no extra effect.
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair();


	// Return an OUT parameter, true if its hit landscape...OUT parameter work by passing reference to and in this case it's
	// going to be passing a reference to an FVector.
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	// we set that to 0.5.That is to represent the fact that in our game the Crosshair is halfway across the screen,it's the
	// same convention as the UI anchors and the like,so it is 50% of the way to the screen.  
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;


	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;
	
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};

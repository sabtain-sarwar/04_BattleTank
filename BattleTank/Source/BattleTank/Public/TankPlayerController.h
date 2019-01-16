// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
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
};

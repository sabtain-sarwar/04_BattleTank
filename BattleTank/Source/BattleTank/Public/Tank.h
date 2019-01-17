// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h" // now the tank has a concept of this TankAimingComponent
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put New includes above

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation); // In this case , we kind of mean the Location of the thing we want to hit,but it is also
	// the HitLocation formally from the LineTrace that we did in the TankPlayerController,because we are wanting to hit the 
	// thing that oyr LineTrace hit.

protected:
	// we are putting it in the protected section.Why protected? Well it can't be private,because we're going to need to access 
	// it using a UPROPPERTY later,and it's not going to be allowed to be private we'll get a compiler error.And it doesn't 
	// need to be public because who needs access to this component from the outside.

	// we're going to make ourself a TankMovementComponent pointer.The TankMovementComponent exist as a class  
	UTankAimingComponent* TankAimingComponent = nullptr; // nullptr just to initialize it to something sensible and predictable.
	// The tank now has the ability to have a refrence to a TankAimingComponent

private:	
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};

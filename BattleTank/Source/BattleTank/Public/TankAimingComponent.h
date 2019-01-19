// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; // Forward Declaration...And that just allows us to refrence the type UTankBarrel in our header file

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// setter method for barrel refrence.If this TankAimingComponent is going to have a barrel member down in private section,
	// then we shouldn't expose that publicly it's generally bad practice.So,we want a setter method
	void SetBarrelRefrence(UTankBarrel* BarrelToSet);
	//void SetBarrelRefrence(UStaticMeshComponent* BarrelToSet);

	void AimAt(FVector HitLocation , float LaunchSpeed);


private:
	UTankBarrel* Barrel = nullptr;
	//UStaticMeshComponent* Barrel = nullptr;  // nullptr as a starting point
	
	void MoveBarrelTowards(FVector AimDirection);
};

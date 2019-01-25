// Copyright Sabtain Sarwar

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state...uint8 (data type you want that enum to use.That's an 8 bit integer,which means 0 and 255.In other
// words you have 256 different possible members you could put in your enum) EFiringState as a type
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};


class UTankBarrel; // Forward Declaration...And that just allows us to refrence the type UTankBarrel in our header file
class UTankTurret;
class AProjectile;

// Holds Barrel's properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// setter method for barrel refrence.If this TankAimingComponent is going to have a barrel member down in private section,
	// then we shouldn't expose that publicly it's generally bad practice.So,we want a setter method
	//void SetBarrelRefrence(UTankBarrel* BarrelToSet);
	//void SetBarrelRefrence(UStaticMeshComponent* BarrelToSet);

	//void SetTurretRefrence(UTankTurret* TurretToSet);

	// The signature is different bcz the AimingComponent need to know the the LaunchSpeed that was dtored on the tank,but now
	// we're going to have a copy of the launchSpeed right here
	// void AimAt(FVector HitLocation , float LaunchSpeed);
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();


protected:
	// Declared a variable which is a variable of type EFiringState, which can only takes the values of EFiringState.And we're
	// initializing it to Reloading
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Locked;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void MoveBarrelTowards(FVector AimDirection);

	UTankBarrel* Barrel = nullptr;
	//UStaticMeshComponent* Barrel = nullptr;  // nullptr as a starting point

	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000; //float LaunchSpeed = 100000; // starting value of 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint; // <class name> and it does not need a pointer bcz that's built into the

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;
};

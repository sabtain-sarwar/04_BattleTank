// Copyright Sabtain Sarwar

#pragma once

//#include "TankAimingComponent.h" // now the tank has a concept of this TankAimingComponent .moved this include to tank.cpp
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put New includes above

// Forward Declarations
// class UTankBarrel; // So,the basic point is that in the header file,if you need access to a type,then you just use a class,a
// forward declaration
// class UTankAimingComponent;
// class UTankMovementComponent;
// class AProjectile; moved to tankAimingComponent.h

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//public bcz other classes need to call this method.TakeDamage,leaves the responsibility for taking the damage in the hands 
	// of the tank.It doesn't have to take damage,but it can decide whether it's going to take damage.But this method will
	// Called by the engine when something like the projectile is in the range and says that damage sould be taken
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor* DamageCauser) override;

	// Return curren health as a percentage of starting health,between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

	FTankDelegate OnDeath;

	//virtual void BeginPlay() override;

	// setter method . This method get the refrence of barrel from Tank_BP Event Graph.We have given it a category=setup because
	// it's setting up the tank.We can call this method from blueprint
	//UFUNCTION(BlueprintCallable , Category = Setup)
	//void SetBarrelRefrence(UTankBarrel* BarrelToSet); 	// void SetBarrelRefrence(UStaticMeshComponent* BarrelToSet);

	//UFUNCTION(BlueprintCallable, Category = Setup)
		//void SetTurretRefrence(UTankTurret* TurretToSet);

	// moved the below method to TankAimingComponent.h
	//void AimAt(FVector HitLocation); // In this case , we kind of mean the Location of the thing we want to hit,but it is also
	// the HitLocation formally from the LineTrace that we did in the TankPlayerController,because we are wanting to hit the 
	// thing that oyr LineTrace hit.

	// UFUNCTION(BlueprintCallable, Category = "Firing") moved to TankAimingComponent
		//void Fire();

protected:
	// we are putting it in the protected section.Why protected? Well it can't be private,because we're going to need to access 
	// it using a UPROPPERTY later,and it's not going to be allowed to be private we'll get a compiler error.And it doesn't 
	// need to be public because who needs access to this component from the outside.

	// we're going to make ourself a TankMovementComponent pointer.The TankMovementComponent exist as a class 
	//UPROPERTY(BlueprintReadOnly)
		//UTankAimingComponent* TankAimingComponent = nullptr; //nullptr just to initialize it to something sensible and predictable.
	// The tank now has the ability to have a refrence to a TankAimingComponent

	//UPROPERTY(BlueprintReadOnly)
	//	UTankMovementComponent* TankMovementComponent = nullptr; // to store the pointer
private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth; // Initialised in BeginPlay()
	
	//int32 CurrentHealth = StartingHealth;
	// below code moved to TankAimingComponent.h
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		
	//UPROPERTY(EditDefaultsOnly, Category = "Setup")
		//TSubclassOf<AProjectile> ProjectileBlueprint; // <class name> and it does not need a pointer bcz that's built into the
	// way the TSubclassOf works.
	//UClass* ProjectileBlueprint; this let's me choose anything,anyclass in blueprint ,because we said in the code here,i want
	// a UClass* a pointer to any UClass.

	//UPROPERTY(EditDefaultsOnly, Category = "Firing") 
		//float LaunchSpeed = 4000; //float LaunchSpeed = 100000; // starting value of 1000 m/s

	//UPROPERTY(EditDefaultsOnly, Category = "Firing")
		//float ReloadTimeInSeconds = 3;

	// Local Barrel Reference for spawning projectile 
	//UTankBarrel* Barrel = nullptr;

	//double LastFireTime = 0;
};

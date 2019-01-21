// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h" 
#include "TankAimingComponent.h" 



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// we're adding the component in the constructor of the tank,because the tank is going to require the TankAimingComponent,
	// if it's going to delegate aiming to it.

	// No need to protect pointers as added at constructor
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

//void ATank::SetBarrelRefrence(UStaticMeshComponent* BarrelToSet)
void ATank::SetBarrelRefrence(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelRefrence(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretRefrence(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretRefrence(TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation , LaunchSpeed);
	//auto OurTankName = GetName(); // This is the current name of the current tank
	//UE_LOG(LogTemp, Warning, TEXT("%s aimimg at %s"), *OurTankName , *HitLocation.ToString());
}

void ATank::Fire()
{
	// Moved to projectile.cpp
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f : Tank Fires"), Time);

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	//if (!Barrel) { return; } now this condition is applied below

	if (Barrel && isReloaded)
	{
		// Spawn the projectile at the socket Location on the barrel....(or projectile in the correct location)(returns projectile)
		auto Projectile = GetWorld()->SpawnActor<AProjectile>( // from getworld you spawn an actor <what type you want me to act>
			ProjectileBlueprint, // Class of the thing you are going to spawn...is the thing we want to spawn          
			Barrel->GetSocketLocation(FName("Projectile")), // where are we going to spawn it? at barrel
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		//projectile and call a method on this 
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
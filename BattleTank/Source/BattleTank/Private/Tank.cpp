// Copyright Sabtain Sarwar

#include "Tank.h"
//#include "TankBarrel.h"
//#include "Projectile.h" 
//#include "TankAimingComponent.h" 
//#include "TankMovementComponent.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// we're adding the component in the constructor of the tank,because the tank is going to require the TankAimingComponent,
	// if it's going to delegate aiming to it.

	// No need to protect pointers as added at constructor
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	// TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component")); 
}

//void ATank::SetBarrelRefrence(UStaticMeshComponent* BarrelToSet)
//void ATank::SetBarrelRefrence(UTankBarrel* BarrelToSet)
//{
//	TankAimingComponent->SetBarrelRefrence(BarrelToSet);
//	Barrel = BarrelToSet;
//}

//void ATank::SetTurretRefrence(UTankTurret* TurretToSet)
//{
//	TankAimingComponent->SetTurretRefrence(TurretToSet);
//}



// Called to bind functionality to input
//void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//}

//void ATank::BeginPlay()
//{
	//Super::BeginPlay(); // Needed for BP Begin Play to run!
	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
//}

//void ATank::AimAt(FVector HitLocation)
//{
	//if (!ensure(TankAimingComponent)) { return; }
//	TankAimingComponent->AimAt(HitLocation , LaunchSpeed);
	//auto OurTankName = GetName(); // This is the current name of the current tank
	//UE_LOG(LogTemp, Warning, TEXT("%s aimimg at %s"), *OurTankName , *HitLocation.ToString());
//}

//void ATank::Fire() Moved to TankAimingComponent.cpp
//{
	// Moved to projectile.cpp
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f : Tank Fires"), Time);
	//if (!ensure(Barrel)) { return; }
	//bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	//if (!Barrel) { return; } now this condition is applied below

	//if (isReloaded)
	//{
		// Spawn the projectile at the socket Location on the barrel....(or projectile in the correct location)(returns projectile)
		//auto Projectile = GetWorld()->SpawnActor<AProjectile>( // from getworld you spawn an actor <what type you want me to act>
		//	ProjectileBlueprint, // Class of the thing you are going to spawn...is the thing we want to spawn          
		//	Barrel->GetSocketLocation(FName("Projectile")), // where are we going to spawn it? at barrel
		//	Barrel->GetSocketRotation(FName("Projectile"))
		//	);
		//projectile and call a method on this 
		//Projectile->LaunchProjectile(LaunchSpeed);
	//LastFireTime = FPlatformTime::Seconds();
	//}
//}

// because the tank is an actor,there is a method that will be called on the tank automatically if it's in that radius and that
//  mewthod is AActor::TakeDamage
float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	// UE_LOG(LogTemp, Warning, TEXT("DamageAmount=%f , DamageToApply=%i"), DamageAmount , DamageToApply);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Died"));
	}
	return DamageToApply; // return the amount of damage that was taken
}
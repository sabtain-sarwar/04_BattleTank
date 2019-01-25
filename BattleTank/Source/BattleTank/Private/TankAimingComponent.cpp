// Copyright Sabtain Sarwar


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

//void UTankAimingComponent::SetBarrelRefrence(UStaticMeshComponent* BarrelToSet)

//void UTankAimingComponent::SetBarrelRefrence(UTankBarrel* BarrelToSet)
//{
//	if(!BarrelToSet) { return; }
//	Barrel = BarrelToSet;
//}

//void UTankAimingComponent::SetTurretRefrence(UTankTurret* TurretToSet)
//{
//	if (!TurretToSet) { return; }
//	Turret = TurretToSet;
//}



void UTankAimingComponent::AimAt(FVector HitLocation , float LaunchSpeed)
{
	//auto OurTankName = GetOwner()->GetName(); 
	//auto BarrelLocation = Barrel->GetComponentLocation().ToString(); // a refrence to barrel and getting its location
	//UE_LOG(LogTemp, Warning, TEXT("%s aimimg at %s from %s"), *OurTankName, *HitLocation.ToString() , *BarrelLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Firing at %f"), LaunchSpeed);
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity // calculate the outLaunchVelocity
	(
		this, // refrence to actual TankAimingComponent
		OutLaunchVelocity, // that is an OUT parameter
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false, // we dont't want to go by the HighArc so we say false
		0, // CollisionRadius.How much variablity do we want on it ? 0 bcz we want to aim precisely
		0, // OverrideGravityZ. No we're not going to do 
		ESuggestProjVelocityTraceOption::DoNotTrace // is that you need to decide whether we're going to trace or not
		// whether we're going to do debug trace. This parameter must be present to prevent bug.
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f : Aim Solution Found") , Time);
	}
	else // no solution found
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f : No aim solve found"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) // Movw the barrel towards a particular AimDirection
{
	//if (!Barrel || !Turret) { return; } 
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	// Where the barrel pointing,compared to where we're asking to point it,and then decide how much we're going to move the 
	// barrel this frame.

	// GetForwardVector().It is just X Direction vector,it is the direction that the barrel faces in.That's the forward vector
	// we're getting .And then from that we can turn that into a rotation.Rotation is roll,pitch and yaw

	// Work-out difference between current barrel rotation,and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation(); // AimDirection and need to convert it into rotation.Output: it want me 
	// to pitch 8 degrees off the horizon,yaw 5 degrees away.We've got a roll, pitch and yaw of the barrel that we're looking
	// to get.
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator : %s"), *BarrelRotator.ToString());

	//Barrel->Elevate(1); // i.e  100% of its speed
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}
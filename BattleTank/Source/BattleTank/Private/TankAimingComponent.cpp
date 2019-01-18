// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelRefrence(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation , float LaunchSpeed)
{
	//auto OurTankName = GetOwner()->GetName(); 
	//auto BarrelLocation = Barrel->GetComponentLocation().ToString(); // a refrence to barrel and getting its location
	//UE_LOG(LogTemp, Warning, TEXT("%s aimimg at %s from %s"), *OurTankName, *HitLocation.ToString() , *BarrelLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Firing at %f"), LaunchSpeed);
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity // calculate the outLaunchVelocity
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
				// whether we're going to do debug trace
			)
		)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
	}
	// if no solution found do nothing
}
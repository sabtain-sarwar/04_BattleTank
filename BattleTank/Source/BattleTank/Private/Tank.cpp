// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// we're adding the component in the constructor of the tank,because the tank is going to require the TankAimingComponent,
	// if it's going to delegate aiming to it.

	// No need to protect pointers as added at constructor
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelRefrence(UStaticMeshComponent* BarrelToSet)
{
	TankAimingComponent->SetBarrelRefrence(BarrelToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
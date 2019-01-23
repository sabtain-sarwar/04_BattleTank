// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false; // bAutoActivate is a property. what this property means is, it doesn't start
	// flying off until we actually fire at it.That's why we activate this property in LaunchProjectile method.This is saying
	// when we construct it don't autoActivate,but as soon as we launch set the velocity,then go ahead and activate so the
	// thing actually fires
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float speed) // Launch projectile at some speed
{
	auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f : Projectile Fires at %f"), Time,speed);
	// The projectile should be facing forward in thje same direction as the barrel.So this ForwardVector will be hopefully
	// the barrel ForwardVector.Once we got the vector it's just the unit vector then we multiply it with speed and that would
	// give us the initial launch velocity.And then we need to activate the projectile movement component
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	ProjectileMovement->Activate(); // Activate is a method.The deactivation that we did on the constructor is then counted by
	// the fact that we've called an activate().
}
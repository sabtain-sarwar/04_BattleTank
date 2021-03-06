// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	// We want to make sure that it attaches itself to the CollisionMesh,because the collisonMesh,the thing that's going to
	// detect what's its hitting,the big canon ball,wants to take with it the particle system
	LaunchBlast->AttachToComponent(RootComponent ,FAttachmentTransformRules::KeepRelativeTransform);
	//LaunchBlast->AttachTo(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false; // bAutoActivate is a property. what this property means is, it doesn't start
	// flying off until we actually fire at it.That's why we activate this property in LaunchProjectile method.This is saying
	// when we construct it don't autoActivate,but as soon as we launch set the velocity,then go ahead and activate so the
	// thing actually fires

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//ImpactBlast->AttachTo(RootComponent);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	//ExplosionForce->AttachTo(RootComponent);
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	// I'm trying to run or access OnComponentHit on a projectile,which actually is not a component,it is an actor.So,what we 
	// need to do is,we need to register that against the CollisionMesh OnComponentHit.
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,// refrence to the context that we're going to apply the damage from,which is the projectile
		ProjectileDamage, // Damage Amount
		GetActorLocation(), // origin of the damage
		ExplosionForce->Radius, // all the actors that are within the radius are going to recieve the 
		// amount of damage that is determined by the projectile damage
		UDamageType::StaticClass(),
		TArray<AActor*>() // array of actors that are going to recieve the damage
	);

	FTimerHandle Timer;
	// We need to go to the world because the worls has in it the TimerManager,and then we can call a SetTimer method on it
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
}

void AProjectile::OnTimerExpire()
{
	Destroy();
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
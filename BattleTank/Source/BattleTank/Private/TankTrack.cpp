// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	// &UTankTrack::OnHit This tells it where to go and find the method,when this event gets triggered
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("i'm hit"));
	// what we do on hit is
	   // Drive the tracks
	   DriveTrack();
	   // Apply sideways forces
	   ApplySidewaysForce();
	   CurrentThrottle = 0;
}


//void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
//{
	//  we are not gonna add the Super:TickComponent() into this method call,which means that the super class TickComponent
	// doesn't get called.Now it's ok in this case because the TickComponent essential just call the Blueprint Tick Event and
	// if you have no Blueprint deriving as we don't have here,no Tick event there then we won't see any problems.But in 
	// it is good practice to add you Super::TickComponent() here and if you do that it's not gonna change the behavior and 
	//  you should do it for good habit

	// Calculate the slippage speed.(What is the slippage speed ? It's the component of the speed in the tank right direction,
	// we're just choosing that as a sideway direction.If there is no slippage,there should be 0,and it it's sliding entirely
	// sideways,the SlippageSpeed will be the same as the speed of the tank.In general use the cosine of the angle between
	// the velocity of the tank,whichever directi0on it's actually going in, and the sideways right vector.So if it's going
	// perfectly sideways the cosign between those 2 angles is 1 ,because the cosign of 0 is 1,and you get the full speed.
	// It it's going forward then the angle is 90 degrees, cosign of 90 degrees is 0 so you get a 0. 
	//auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work-out the required acceleration this frame to correct.(So if we're moving sideways at 10 cm as Second,then the frame
	// in the DeltaTime we're gonna need a certain amount of acceleration to fix that velocity back to 0 sideway)(Acceleration
	// is speed over time)DeltaTime tells us how much acceleration we need in this frame.We don't want to apply the acceleration
	// in the direction we're slipping,we want to apply it in the opposite direction to what we're slipping in.That's  why we 
	// put a minus here
	//auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideway force (F = m a)..GetOwnwer goes up and get the Tank_BP from the track.Once we get the Owner 
	// we look throught that pointer,provided that we can find an owner.And then we get the root component which is where we 
	// go down and find the root component.What comes out of that TankRoot ?It's a USceneComponent pointer which is the Tank 
	// root component(Tank).StaticMeshComponent is a specialization of SceneComponent,but we need a StaticMeshComponent in 
	// order to actually get fro the tank,the mass.Because if we look on the tank Blueprint,it's the fact that it's a
	// static mesh  ,and the physics property is giving us a mass.So what we need to do with the tank root is ,we need to cast
	// it to the UStaticMeshComponent in order to be able to get the properties that we want from it.When we look through the
	// pointer of tankRoot we can just AddForce.That's why we had to cast it ,it gives us all these  methods
	//auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	//auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two Tracks
	//TankRoot->AddForce(CorrectionForce);
//}

void UTankTrack::ApplySidewaysForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two Tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	// We don't want this to exceed 1,so we use a FMath::clamp on that and we restrict the range to -1 to 1.Now we want to be
	// explicit that we want a floating point value out of this not an integer value
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle , -1 , 1);

	// moved this to TankMovementComponent.cpp
	//auto Name = GetName(); 
    //UE_LOG(LogTemp, Warning, TEXT("%s Throttle : %f"), *Name , Throttle);

	// video 148
	// forwardVector of the track along X-axes.If Throttle is 0 you get no force,if the force is 1 ,you get the MaxDrivingForce.
	// If the throttle is -1,you get backwards force
	//auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	//auto ForceLocation = GetComponentLocation(); // location on which we apply the force.it's going to be the location of tracks

	// Then we are going to apply force(add a force to tank root component and it is a static mesh).So how do we get the root
	// component.Lets start by saying,use an auto so we know what we're getting back.Firstly we GetOwner().What do we have if
	// we GetOwner() ? What type do we get back ? We get an Actor(it is this guy Tank_BP.It is the tank itself.So that is the
	// owner of the track) and then we get the root component from the owner(So,we go up to the owner then down to the root
	// component).Then what we han in auto ,a USceneComponent pointer which is the tank in the BP.StaticMeshComponent is also
	// called USceneComponent.we can apply force on UprimitiveComponent but not on USceneComponent
	//auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation); 
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation(); 
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
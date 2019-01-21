// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"




void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName(); 
    UE_LOG(LogTemp, Warning, TEXT("%s Throttle : %f"), *Name , Throttle);
	// video 148
	// forwardVector of the track along X-axes.If Throttle is 0 you get no force,if the force is 1 ,you get the MaxDrivingForce.
	// If the throttle is -1,you get backwards force
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation(); // location on which we apply the force.it's going to be the location of tracks

	// Then we are going to apply force(add a force to tank root component and it is a static mesh).So how do we get the root
	// component.Lets start by saying,use an auto so we know what we're getting back.Firstly we GetOwner().What do we have if
	// we GetOwner() ? What type do we get back ? We get an Actor(it is this guy Tank_BP.It is the tank itself.So that is the
	// owner of the track) and then we get the root component from the owner(So,we go up to the owner then down to the root
	// component).Then what we han in auto ,a USceneComponent pointer which is the tank in the BP.StaticMeshComponent is also
	// called USceneComponent.we can apply force on UprimitiveComponent but not on USceneComponent
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation); 
}
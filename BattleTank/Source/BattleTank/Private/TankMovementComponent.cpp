// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

// 1st parameter is what velocity do i need the tank to move in this frame
void  UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super as we are replacing the functionality
	//auto TankName = GetOwner()->GetName();
	//auto MoveVelocityString = MoveVelocity.ToString(); // Not a unit vector.This vector is long
	//UE_LOG(LogTemp, Warning, TEXT("%s Velocity to : %s"), *TankName , *MoveVelocityString);
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal(); // tank forward direction. How do you get the tank
	// forward  ? We're on TankMovementComponet,what do we do to go from the MovementComponent to the tank itself ?--------
	// is  a unit vector,in the direction the tank is facing forward.Vector in the direction of X-Axes where the tank is looking
	auto AiForwardIntention = MoveVelocity.GetSafeNormal(); // normalize the vector.That is the unit vector in which AI intends
	// for the tank to move forward.It is a unit vector in a direction the AI would like the tank to move.
	auto ForwardThrow = FVector::DotProduct(TankForward, AiForwardIntention);

	IntendMoveForward(ForwardThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forword throw : %f"), Throw);
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend turn right throw : %f"), Throw);
	// If we're to turn right, the left track going to go forward and the right track going to go backward.So,if we are fully
	// with full throw turning right,then this is what happenes(Right track minus parameter) anf if you partially turning
	// right then you'll have both of these track set to partial throttle.
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
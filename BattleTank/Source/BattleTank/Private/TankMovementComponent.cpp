// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
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
	UE_LOG(LogTemp, Warning, TEXT("Intend turn right throw : %f"), Throw);
	// If we're to turn right, the left track going to go forward and the right track going to go backward.So,if we are fully
	// with full throw turning right,then this is what happenes(Right track minus parameter) anf if you partially turning
	// right then you'll have both of these track set to partial throttle.
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
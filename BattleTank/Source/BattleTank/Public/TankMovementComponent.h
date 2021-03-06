// Copyright Sabtain Sarwar

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;

/**
 * Responsible from driving the tank track
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	// This is going to communicate the movement desire.It take in a float because it's going to  be between -1 and +1,and i'm
	// going to call that float Throw,which is the control throw,it's how far forward or back the control is moved.Video 151 and
	// read the blueprint
	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendTurnRight(float Throw);

	
	
private:
	// put override on the end, which makes the compiler checks this is exactly the right signature
	// Called from the pathfinding logic by the AI Controller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};

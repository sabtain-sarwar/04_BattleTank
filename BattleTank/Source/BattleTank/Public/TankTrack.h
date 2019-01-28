// Copyright Sabtain Sarwar

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	// Set a thgrottle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);
	
	// Max  force per track,in Newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000; // assume 40 tone tank,and 1g acceleration

private:
	
	UTankTrack();

	// virtual because that's what it is in the parent class. void because that's what comes back,and we have to type override
	// because we want to make sure that we're overiding a method in the parent class,with exactly that signature
	virtual void BeginPlay() override;

	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void ApplySidewaysForce(); 

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();

	float CurrentThrottle = 0;

};

// Copyright Sabtain Sarwar


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
// #include "Tank.h" 
#include "Tank.h" 

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank Death's event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossedTankDeath);
	}
}

void ATankPlayerController::OnPossedTankDeath()
{
	StartSpectatingOnly();
}


void ATankPlayerController::BeginPlay()
{
	// We want to start always by going Super::BeginPlay().Now, what that does is ,it makes sure that the BeginPlay() on the
	// Super:: classes is being called.(Called the default behavior before we do anything)
	Super::BeginPlay();

	//auto ControlledTank = GetControlledTank();
	//if (!ControlledTank) 
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing the tank"));
	//} 
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlayerController  possessing : %s") , *(ControlledTank->GetName()));
	//}

	//auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	} 
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController can't find aiming component at begin play"));
	}
}

void  ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

//ATank* ATankPlayerController::GetControlledTank() const
//{
	// return Cast<ATank>(GetPawn()); it just returns the Pawn ,and it actually doesn't need to cast this Pawn to a Tank,bcz
	// tank is a Pawn.
	//return GetPawn();
//}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // e.g; if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation; // OUT Parameter
	// The parameter is going to be used as the OUT parameter 
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation : %i"), bGotHitLocation);
	if (bGotHitLocation) // has "side-effect" , is going to line trace 
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation : %s"), *HitLocation.ToString());
		
		//  Tell controlled tank to aim at this point
		// GetControlledTank()->AimAt(HitLocation);
		AimingComponent->AimAt(HitLocation);
	}
}

// Get world location Of linetrace through crosshair , true if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation : %s"), *ScreenLocation.ToString());

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation , LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("LookDirection : %s"), *LookDirection.ToString());
		// Line trace along that look direction , and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation ) const
{
	FHitResult HitResult; // to store our HitResult
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Camera) //ECC_Visibility that tells us that i want u 2 go out and hit anything which is visible
		) // the type that comes out of the line trace is HitResult,so the way we get get the HitLocation is we go the HitResult
		// which is not in itself the vector we want,and then we go dot and there we got something called Location
	{
		HitLocation = HitResult.Location; // if we look at that then that is actually the FVector type we're looking for
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line Trace didn't succeed
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation ,FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
	    ScreenLocation.Y,
		CameraWorldLocation, // it's actually the camera.we don't need that but we need to provide a variable so that it can
		//split the camera world location into it
		LookDirection //we're looking for the direction we're looking in
	);
}
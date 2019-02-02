// Copyright Sabtain Sarwar


#include "TankAIController.h"
#include "TankAimingComponent.h"
//#include "Tank.h"
#include "Tank.h" // so we can implement onDeath

void ATankAIController::BeginPlay()
{
	// We want to start always by going Super::BeginPlay().Now, what that does is ,it makes sure that the BeginPlay() on the
	// Super:: classes is being called.(Called the default behavior before we do anything)
	Super::BeginPlay();

	//auto PlayerTank = GetPlayerTank();
	//if (!PlayerTank)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AIController  found player : %s"), *(PlayerTank->GetName()));
//	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) 
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if(!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank Death's event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}

void ATankAIController::OnPossedTankDeath()
{
	//UE_LOG(LogTemp, Warning, TEXT(" Received! "));
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void  ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	//if (GetPlayerTank()) // 1st we need to check do we have a player tank
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	//if (ensure(PlayerTank))
	//{
		// move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);// check radius in cm

		// Aims towards the player.... (once we got the controlled tank,then it will have an AimAT() method on it).
		//GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation()); //we tell the CntrolledTank 2 aim at the playr location
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		
		// Fire if ready
		//ControlledTank->Fire();
		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}
		
	//}
}



//Tank* ATankAIController::GetControlledTank() const
//{
	//return Cast<ATank>(GetPawn());
//}


//ATank* ATankAIController::GetPlayerTank() const
//{
	//auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	//if (!PlayerPawn) { return nullptr; }
	//return Cast<ATank>(PlayerPawn);
//}
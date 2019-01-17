// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	// We want to start always by going Super::BeginPlay().Now, what that does is ,it makes sure that the BeginPlay() on the
	// Super:: classes is being called.(Called the default behavior before we do anything)
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController  found player : %s"), *(PlayerTank->GetName()));
	}
}

void  ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) // 1st we need to check do we have a player tank
	{
		// move towards the player

		// Aims towards the player.... (once we got the controlled tank,then it will have an AimAT() method on it).
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation()); //we tell the CntrolledTank 2 aim at the playr location

		// Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}
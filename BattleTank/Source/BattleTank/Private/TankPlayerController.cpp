// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	// We want to start always by going Super::BeginPlay().Now, what that does is ,it makes sure that the BeginPlay() on the
	// Super:: classes is being called.(Called the default behavior before we do anything)
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing the tank"));
	} 
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController  possessing : %s") , *(ControlledTank->GetName()));
	}
}

void  ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	// Get world location if linetrace through crosshair
	// if it hits the landscape
	   //  Tell controlled tank to aim at this point
}
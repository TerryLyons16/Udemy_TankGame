// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();



	ATank* possessedTank = GetControlledTank();

	if (possessedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player's possessed tank is %s"),*possessedTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player's possessed tank is null"));
	}

}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank())
	{
		//Exit if the player is not controlling a tank
		return;
	}

	FVector HitLocation; //Out parameter
	//Get World crosshair location
	if (GetSightRayHitLocation(HitLocation))
	{

		GetControlledTank()->AimAt(HitLocation);
	}

	//if it hits the landscape/object
		//Have the tank aim at that location

}

//Get the world location of the crosshair. Returns true if an object is hit by the ray trace
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.f);

	//Find the crosshair screen position
	FVector2D CrosshairLocation = GetCrosshairScreenLocation();

	//Deproject screen position to world direction
	
	FVector LookDirection;
	FVector LookLocation;
	if (GetCrosshairWorldLocation(CrosshairLocation, LookLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookLocation,LookDirection, AimRange, OutHitLocation);
	}
	//If no location found, set vector to 0
	OutHitLocation = FVector(0.f);
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookLocation, FVector lookVector, float LookRange, FVector & OutHitLocation) const
{

	//Linetrace by channel along world look direction
	
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetControlledTank());
	//Set use complex trace to false to trace using simple scene collision meshes, use GetOwner() as the actor to ignore

	FHitResult TraceHitResult;
	auto StartLocation = lookLocation;
	auto EndLocation = StartLocation + (lookVector*LookRange);

	if (GetWorld()->LineTraceSingleByChannel(TraceHitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, TraceParams))
	{
		OutHitLocation = TraceHitResult.Location;
		return true;
	}


	return false;
}

FVector2D ATankPlayerController::GetCrosshairScreenLocation() const
{
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);



	return FVector2D(viewportSizeX*CrosshairXLocation,viewportSizeY*CrosshairYLocation);
}

bool ATankPlayerController::GetCrosshairWorldLocation(FVector2D ScreenLocation, FVector &OutLookLocation,FVector &OutLookDirection) const
{
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OutLookLocation, OutLookDirection);
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
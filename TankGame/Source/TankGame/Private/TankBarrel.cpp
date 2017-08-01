// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{

	//Get the difference between the current rotation and the aim direction

	//Move the barrel for this frame, given a max elevation speed and frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float ElevationChange = RelativeSpeed *MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;//Use DeltaTimeSeconds to make the change framerate independant

	float Elevation = FMath::Clamp<float>(RelativeRotation.Pitch, MinAimAngleDegrees, MaxAimAngleDegrees) + ElevationChange;

	SetRelativeRotation(FRotator(Elevation, 0.f, 0.f));

}



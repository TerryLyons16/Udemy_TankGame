// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	if (!(FMath::Abs(RelativeSpeed) < 180)) //Ensures that the turret will always take the shortest path to the desired rotation
	{
		RelativeSpeed = -RelativeSpeed;
	}

	//Get the difference between the current rotation and the aim direction

	//Move the barrel for this frame, given a max elevation speed and frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float YawChange = RelativeSpeed *MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;//Use DeltaTimeSeconds to make the change framerate independant

	float Yaw = RelativeRotation.Yaw + YawChange;
	
	//FQuat newRotation=FQuat()


	SetRelativeRotation(FRotator(0.f, Yaw, 0.f));


}



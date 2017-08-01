// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), hidecategories=("Collision") )
class TANKGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
		//-1 is max downwards movement, +1 is max upwards movement
		void ElevateBarrel(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category="Aiming")
	float MaxDegreesPerSecond =10;
	
	UPROPERTY(EditAnywhere, Category="Aiming")
	float MinAimAngleDegrees = 0.f;

	UPROPERTY(EditAnywhere, Category="Aiming")
	float MaxAimAngleDegrees = 40.f;
};

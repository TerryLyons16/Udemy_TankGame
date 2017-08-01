// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward declaration
class ATank;
/**
 * 
 */
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

		//Move the tank's turret to point towards where the crosshair intersects with the world
		void AimAtCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	FVector2D GetCrosshairScreenLocation() const;
	bool GetCrosshairWorldLocation(FVector2D ScreenLocation, FVector &OutLookLocation, FVector &OutLookDirection) const;


	ATank* GetControlledTank() const;

	
public:

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
		float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
		float CrosshairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
		float AimRange = 1000000.f;

	bool GetLookVectorHitLocation(FVector lookLocation, FVector lookVector, float LookRange, FVector &OutHitLocation) const;

};


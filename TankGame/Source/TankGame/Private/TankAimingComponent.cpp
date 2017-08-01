// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UTankAimingComponent::AimAt(FVector target, float FiringSpeed)
{
	if (!Barrel||!Turret)//Pointer protection
	{
		return;
	}

	FVector OutLaunchVelocity;

	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileStart"));

	bool AimSolutionFound = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, target, FiringSpeed, false, 0.f, 0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace , FCollisionResponseParams::DefaultResponseParam, TArray<AActor *>(), false);
	//Set ESuggestProjVelocityTraceOption to DoNotTrace to prevent issue with solutions not being found (seems to only trace single arc (i.e. high/low arc based on parameter) when set like this)

	if (AimSolutionFound)
	{

		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);
		float time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Tank %s is aiming at: %s"), time, *GetOwner()->GetName(), *AimDirection.ToString());
	}
	else
	{
		float time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution not found"), time);
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel||!Turret)//Pointer protection
	{
		return;
	}


	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimDirectionRotator = AimDirection.Rotation();

	FRotator DeltaRotator = AimDirectionRotator - BarrelRotator;

	Barrel->ElevateBarrel(DeltaRotator.Pitch);

	Turret->Rotate(DeltaRotator.Yaw);



}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * barrelRef)
{
	Barrel = barrelRef;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * turretRef)
{
	Turret = turretRef;
}




// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();



	ATank* possessedTank = GetControlledTank();

	if (possessedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s's possessed tank is %s"), *GetNameSafe(this), *possessedTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s's possessed tank is null"),*GetNameSafe(this));
	}

	ATank* playerTank = GetPlayerTank();
	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has found player tank %s"), *GetNameSafe(this), *playerTank->GetName());
	}

}



void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if(GetPlayerTank())
	{
		//TODO Move towards the player

		//Aim at the player
		AimAtPlayer();

		//TODO Fire if ready
	}

	
}

void ATankAIController::AimAtPlayer()
{
	if (!(GetControlledTank()&& GetPlayerTank()))
	{
		return;
	}

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto playerTank =GetWorld()->GetFirstPlayerController()->GetPawn();

	return Cast<ATank>(playerTank);;
}





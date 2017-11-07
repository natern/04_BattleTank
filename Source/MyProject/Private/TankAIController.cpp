// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankAIController.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
	if(!tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController couldn't find tank."));
	}
	GetPlayerTank();
}

ATank* ATankAIController::GetControlledTank() const
{
	return(Cast<ATank>(GetPawn()));
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto player = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
	if(player)
	{
		return(player->GetControlledTank());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController couldn't find player."));
		return(nullptr);
	}
}

void ATankAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	Aim();
}

void ATankAIController::Aim()
{
	ATank* targetTank = GetPlayerTank();
	ATank* controlledTank = GetControlledTank();
	if(targetTank && controlledTank)
	{
		controlledTank->AimAt(targetTank->GetTargetLocation(controlledTank));
	}
}
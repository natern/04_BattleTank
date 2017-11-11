// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankAIController.h"
#include "Tank.h"
#include "TankPlayerController.h"

ATankAIController::ATankAIController() :
	fireConstantly(false),
	acceptanceRadius(3000.f)
{
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	Aim();
}

void ATankAIController::Aim()
{
	ATank* controlledTank = Cast<ATank>(GetPawn());
	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(playerTank && controlledTank)
	{
		MoveToActor(playerTank, acceptanceRadius);
		controlledTank->AimAt(playerTank->GetTargetLocation(controlledTank));
		if (fireConstantly)
		{
			controlledTank->Fire();
		}
	}
}

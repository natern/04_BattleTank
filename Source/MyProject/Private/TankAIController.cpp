// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"

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
	APawn* controlledTank = GetPawn();
    UTankAimingComponent* aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
	APawn* playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if(playerTank && controlledTank)
	{
		MoveToActor(playerTank, acceptanceRadius);
        aimingComponent->AimAt(playerTank->GetTargetLocation(controlledTank));
		if(fireConstantly && aimingComponent->GetFiringState() == EFiringState::E_READY)
		{
            aimingComponent->Fire();
		}
	}
}

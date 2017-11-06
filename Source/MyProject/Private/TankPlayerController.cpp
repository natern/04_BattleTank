// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Tank.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return(Cast<ATank>(GetPawn()));
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
	if (tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController controlling %s"), *(tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController couldn't find tank."));
	}
	AimRaycast();
}

void ATankPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Tick Tock! (%f)"), deltaSeconds);
}

void ATankPlayerController::AimRaycast()
{

}
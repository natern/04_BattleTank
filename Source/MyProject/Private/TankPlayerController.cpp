// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

    ATank* tank = GetControlledTank();
    if(ensure(tank))
    {
        UTankAimingComponent* tankAimingComponent = tank->FindComponentByClass<UTankAimingComponent>();
        if(ensure(tankAimingComponent))
        {
            FoundAimingComponent(tankAimingComponent);
        }
    }
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return(Cast<ATank>(GetPawn()));
}

void ATankPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	Aim();
}

void ATankPlayerController::Aim()
{
	if(!ensure(GetControlledTank()))
	{
		return;
	}
	FVector hitLocation; //Out parameter
	if(DoRaycast(hitLocation) || !hitLocation.IsZero())
	{
		GetControlledTank()->AimAt(hitLocation);
	}
}

bool ATankPlayerController::DoRaycast(FVector& hitLocation) const
{
	int32 viewportSizeX, viewPortSizeY;
	GetViewportSize(viewportSizeX, viewPortSizeY);
	FVector2D reticulePos(viewportSizeX * reticuleX, (static_cast<float>(viewPortSizeY) * reticuleY));
	FVector cameraLocation, aimDirection;
	if (DeprojectScreenPositionToWorld(reticulePos.X, reticulePos.Y, cameraLocation, aimDirection))
	{
		const FVector aimEndpoint(cameraLocation + aimDirection * rayLength);
		FHitResult result;
		if (GetWorld()->LineTraceSingleByChannel(result, cameraLocation, aimEndpoint, ECollisionChannel::ECC_Visibility))
		{
			hitLocation = result.Location;
			return(true);
		}
		else
		{
			hitLocation = aimEndpoint;
			return(false);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DoRaycast failed to Deproject screen position"));
	}
	hitLocation = FVector(0.f);
	return(false);
}
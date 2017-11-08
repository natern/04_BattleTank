// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankPlayerController.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if(wWidgetType)
	{
		mReticule = CreateWidget<UUserWidget>(this, wWidgetType);
		if(mReticule)
		{
			mReticule->AddToViewport();
		}
		//Todo: cleanup reticule on end, if that's necessary
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
	if (!GetControlledTank())
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
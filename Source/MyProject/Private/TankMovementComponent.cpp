// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankMovementComponent.h"
#include "TankTreadComponent.h"

UTankMovementComponent::UTankMovementComponent() :
	trackLeft(nullptr),
	trackRight(nullptr),
	leftThrottle(0.f),
	rightThrottle(0.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UTankMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!ensure(trackLeft && trackRight))
	{
		return;
	}

	auto tank = GetOwner();
	if(!ensure(tank))
	{
		return;
	}
	
	auto playerController = Cast<APlayerController>(tank->GetInstigatorController());
	if (playerController)
	{
		if(playerController->IsInputKeyDown(forwardKey))
		{
			if(playerController->IsInputKeyDown(leftKey))
			{
				leftThrottle = -0.25f;
				rightThrottle = 1.f;
			}
			else if (playerController->IsInputKeyDown(rightKey))
			{
				leftThrottle = 1.f;
				rightThrottle = -0.25f;
			}
			else
			{
				leftThrottle = rightThrottle = 1.f;
			}
		}
		else if(playerController->IsInputKeyDown(reverseKey))
		{
			if (playerController->IsInputKeyDown(leftKey))
			{
				leftThrottle = 1.f;
				rightThrottle = -0.25f;
			}
			else if (playerController->IsInputKeyDown(rightKey))
			{
				leftThrottle = -0.25f;
				rightThrottle = 1.f;
			}
			else
			{
				leftThrottle = rightThrottle = -1.f;
			}
		}
		else
		{
			if (playerController->IsInputKeyDown(leftKey))
			{
				leftThrottle = -1.f;
				rightThrottle = 1.f;
			}
			else if (playerController->IsInputKeyDown(rightKey))
			{
				leftThrottle = 1.f;
				rightThrottle = -1.f;
			}
			else
			{
				leftThrottle = rightThrottle = 0.f;
			}
		}

		//auto tankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s moving to %f, %f"), *tankName, rightThrottle, leftThrottle);
	}
	if (leftThrottle != 0.f)
	{
		trackLeft->SetThrottle(leftThrottle);
	}
	if(rightThrottle != 0.f)
	{
		trackRight->SetThrottle(rightThrottle);
	}
	rightThrottle = leftThrottle = 0.f;
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// Replace Super functionality since tanks have unique movement
	FVector moveDir(MoveVelocity);
	moveDir.Z = 0.f;
	if (moveDir.SizeSquared() > 0.f) //make sure we still want to move
	{
		moveDir = moveDir.GetSafeNormal();
		auto tankFacing = GetOwner()->GetActorForwardVector();
		tankFacing.Z = 0;
		float forwardComponent = FVector::DotProduct(tankFacing, moveDir);
		
		auto cross = FVector::CrossProduct(tankFacing, moveDir);
		IntendMoveForwardAnalog(forwardComponent);
		IntendMoveRightAnalog(cross.Z);

		auto tankName = GetOwner()->GetName();
		auto velocityStr = MoveVelocity.ToString();
		//UE_LOG(LogTemp, Warning, TEXT("%s moving to %s"), *tankName, *velocityStr);
	}
}

void UTankMovementComponent::Initialize(UTankTreadComponent* leftTrack, UTankTreadComponent* rightTrack)
{
	trackLeft = leftTrack;
	trackRight = rightTrack;
}

void UTankMovementComponent::IntendMoveForwardAnalog(float val)
{
	leftThrottle += val;
	rightThrottle += val;
}

void UTankMovementComponent::IntendMoveRightAnalog(float val)
{
	leftThrottle += val;
	rightThrottle += -val;
}

void UTankMovementComponent::IntendMoveForward()
{
	leftThrottle = 1.f;
	rightThrottle = 1.f;
}

void UTankMovementComponent::IntendMoveReverse()
{
	leftThrottle = -1.f;
	rightThrottle = -1.f;
}

void UTankMovementComponent::IntendTurnLeft()
{
	leftThrottle = -1.f;
	rightThrottle = 1.f;
}

void UTankMovementComponent::IntendTurnRight()
{
	leftThrottle = 1.f;
	rightThrottle = -1.f;
}


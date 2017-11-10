// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankTreadComponent.h"

UTankTreadComponent::UTankTreadComponent() :
	maxDrivingForce(800000)
{
}

void UTankTreadComponent::SetThrottle(float val)
{
	val = FMath::Clamp<float>(val, -1.f, 1.f) * maxDrivingForce;
	FVector force = GetForwardVector() * val;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* root = Cast<UPrimitiveComponent>(GetAttachmentRoot());
	root->AddForceAtLocation(force, forceLocation);
}



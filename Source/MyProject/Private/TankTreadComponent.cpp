// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankTreadComponent.h"

UTankTreadComponent::UTankTreadComponent() :
	maxDrivingForce(800000)
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTreadComponent::BeginPlay()
{
    Super::BeginPlay();
    OnComponentHit.AddDynamic(this, &UTankTreadComponent::OnHit);
}

void UTankTreadComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    //if(GetWorld()->GetTimeSeconds() - lastHitTime < timeUntilAirborne)
    {
        ApplyDrivingForce();
        CancelSidewaysMovement();
    }
}

void UTankTreadComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    lastHitTime = GetWorld()->GetTimeSeconds();
}

void UTankTreadComponent::SetThrottle(float val)
{
    currentThrottle = val;
}

void UTankTreadComponent::ApplyDrivingForce()
{
    currentThrottle = FMath::Clamp<float>(currentThrottle, -1.f, 1.f) * maxDrivingForce;
    FVector force = GetForwardVector() * currentThrottle;
    FVector forceLocation = GetComponentLocation();
    UPrimitiveComponent* root = Cast<UPrimitiveComponent>(GetAttachmentRoot());
    root->AddForceAtLocation(force, forceLocation);
    currentThrottle = 0.f;
}

void UTankTreadComponent::CancelSidewaysMovement()
{
    float sidewaysSpeed = FVector::DotProduct(GetForwardVector(), ComponentVelocity);
    FVector sidewaysAccel = sidewaysSpeed * GetRightVector() / GetWorld()->GetDeltaSeconds();
    UStaticMeshComponent *tank = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    float mass = tank->GetMass();
    FVector correctiveForce = -mass * sidewaysAccel * 0.5f;
    tank->AddForce(correctiveForce);
}
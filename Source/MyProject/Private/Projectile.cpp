// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
    SetRootComponent(collisionMesh);
    collisionMesh->SetNotifyRigidBodyCollision(true);
    collisionMesh->SetVisibility(false);

	moveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	if (moveComponent)
	{
		moveComponent->bAutoActivate = true;
	}
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
    collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Launch(float speed)
{
	moveComponent->InitialSpeed = speed;
	moveComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	moveComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    OnImpact(this);
}
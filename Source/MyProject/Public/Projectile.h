// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class MYPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
    UFUNCTION(BlueprintImplementableEvent, Category = "State")
    void OnImpact(AProjectile* projectile);

	void Launch(float speed);

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* collisionMesh;

	UProjectileMovementComponent* moveComponent;

private:
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};

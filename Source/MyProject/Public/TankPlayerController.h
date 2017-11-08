// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UUserWidget;
class ATank;
/**
 * 
 */
UCLASS()
class MYPROJECT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> wWidgetType;

	UPROPERTY(EditDefaultsOnly)
	float reticuleX = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float reticuleY = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
	float rayLength = 500000;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;
	ATank* GetControlledTank() const;



	UUserWidget* mReticule;
private:
	void Aim();
	bool DoRaycast(FVector& hitLocation) const;
};

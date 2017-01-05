// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 *
 */
UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

  ATank* GetControlledTank() const;
  virtual  void BeginPlay() override;
  virtual void Tick(float deltatime) override;
  void AimTowardsCrosshair();
  bool GetSightRayHitLocation(FVector& HitLocation) const;

  UPROPERTY( EditAnywhere )
    float CrosshairXLocation = .5;

  UPROPERTY( EditAnywhere )
    float CrosshairYLocation = .33333;

  UPROPERTY( EditAnywhere )
    float LineTraceRange = 1000000;

  bool GetLookDirection(FVector2D& ScreenLocation, FVector& LookDirection) const;

  bool GetLookVectorHitLocation(FVector& LookDirection, FVector& HitLocation) const;
};

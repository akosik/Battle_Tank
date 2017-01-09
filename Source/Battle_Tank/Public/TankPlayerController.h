// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 *
 */
UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

          protected:
  UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);

 private:
  virtual  void BeginPlay() override;

  virtual void Tick(float deltatime) override;

  void AimTowardsCrosshair();

  bool GetSightRayHitLocation(FVector& HitLocation) const;

  void SetPawn(APawn* InPawn);

  UFUNCTION()
    void OnTankDeath();

  UPROPERTY( EditDefaultsOnly )
    float CrosshairXLocation = .5;

  UPROPERTY( EditDefaultsOnly )
    float CrosshairYLocation = .33333;

  UPROPERTY( EditDefaultsOnly )
    float LineTraceRange = 1000000;

  bool GetLookDirection(FVector2D& ScreenLocation, FVector& LookDirection) const;

  bool GetLookVectorHitLocation(FVector& LookDirection, FVector& HitLocation) const;

  UTankAimingComponent* AimComp;
};

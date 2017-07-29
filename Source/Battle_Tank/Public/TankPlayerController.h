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

public:
  UFUNCTION(BlueprintCallable, Category = "Respawn")
  bool GetReadyToRespawn();

  UFUNCTION(BlueprintCallable, Category = "Respawn")
    void ToggleReadyToRespawn();

protected:
  UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);

  // Changes current controller state to playing, this must be called after possess in order for the controller to take control of the pawn
  UFUNCTION(BlueprintCallable, Category = "Respawn")
    void ChangeToPlayingState();

  // Changes current controller state to spectating, this is called on tank death
  UFUNCTION(BlueprintCallable, Category = "Respawn")
    void ChangeToSpectatingState();

  UFUNCTION(BlueprintNativeEvent, Category = "Death")
  void OnTankDeath();

  UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Respawn")
    float RespawnTime = 5.f;

 private:
  virtual  void BeginPlay() override;

  virtual void Tick(float deltatime) override;

  void AimTowardsCrosshair();

  bool GetSightRayHitLocation(FVector& HitLocation) const;

  void SetPawn(APawn* InPawn);

  UPROPERTY( EditDefaultsOnly )
    float CrosshairXLocation = .5;

  UPROPERTY( EditDefaultsOnly )
    float CrosshairYLocation = .33333;

  UPROPERTY( EditDefaultsOnly )
    float LineTraceRange = 1000000;

  bool GetLookDirection(FVector2D& ScreenLocation, FVector& LookDirection) const;

  bool GetLookVectorHitLocation(FVector& LookDirection, FVector& HitLocation) const;

  UTankAimingComponent* AimComp;

  bool bIsReadyToRespawn = false;
  bool bIsAlive = false;
};

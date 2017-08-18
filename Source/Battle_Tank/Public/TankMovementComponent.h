// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankTrack.h"
#include "TankMovementComponent.generated.h"

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = (Custom) )
class BATTLE_TANK_API UTankMovementComponent : public UNavMovementComponent
{
  GENERATED_BODY()
    
public:
    UTankMovementComponent();
    
  UFUNCTION(BlueprintCallable, Category = "Setup")
    void InitializeMovementComponent(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

  UFUNCTION(BlueprintCallable, Category = "Input")
    void IntendMoveForward(float Throw);

  UFUNCTION(BlueprintCallable, Category = "Input")
    void IntendTurnRight(float Throw);

 private:
  virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

  UTankTrack* LeftTrack = nullptr;
  UTankTrack* RightTrack = nullptr;
};

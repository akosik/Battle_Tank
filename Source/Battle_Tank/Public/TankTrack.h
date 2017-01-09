// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

          public:
  UFUNCTION(BlueprintCallable, Category = Input)
    void SetThrottle(float Throttle);

  void DriveTrack();

  UPROPERTY(EditDefaultsOnly)
    float MaxDrivingForce = 400000;

 private:
  UTankTrack();

  virtual void BeginPlay() override;

  UFUNCTION()
  void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

  void ApplySidewaysForce();

  float CurrentThrottle;


};

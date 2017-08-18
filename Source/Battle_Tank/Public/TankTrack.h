// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "TankWheel.h"
#include "TankTrack.generated.h"

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankTrack : public UPrimitiveComponent
{
	GENERATED_BODY()

          public:
  UFUNCTION(BlueprintCallable, Category = "Input")
    void SetThrottle(float Throttle);

  void DriveTrack(UPrimitiveComponent* Wheel);

  UFUNCTION(BlueprintCallable, Category = "Setup")
    void InitializeTrack(UInstancedStaticMeshComponent* TileToSet, USplineComponent* SplineToSet, TArray<UTankWheel*> WheelsToSet);
  
  void UpdateTrackSpline(float DeltaTime);

  void InstanceTilesAlongTrack();

  void UpdateTrackTiles(float DeltaTime);

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxDrivingForce = 400000;

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float SuspensionLength;

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float SuspensionDamping;

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float SuspensionStiffness;

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 TreadsPerTrack = 100;

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float AntiSlippageCoefficient = .5;

 private:
  UTankTrack();

  void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction);

  void ApplySidewaysForce();

  void AddSuspensionForceForWheel(UTankWheel* Wheel, const float SuspensionVelocity);

  float CalculateWrappedTrackTileDistanceAlongSpline(float UnwrappedDistance);

  float CurrentThrottle;

  UInstancedStaticMeshComponent* TrackTiles;
  USplineComponent* TrackSpline;
  TArray<UTankWheel*> Wheels;

  float TileDisplacementAlongSpline = 0.0f;
  float InstancingStep;


  
};

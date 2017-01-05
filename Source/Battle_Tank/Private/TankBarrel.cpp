// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
  RelativeSpeed = FMath::Clamp<float>(RelativeSpeed,-1,1);
  float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
  float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
  float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

  SetRelativeRotation(FRotator(Elevation, 0 ,0));
}

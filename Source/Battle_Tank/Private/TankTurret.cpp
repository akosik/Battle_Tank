// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
  RelativeSpeed = FMath::Clamp<float>(RelativeSpeed,-1,1);
  float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
  float Rotation = RelativeRotation.Yaw + RotationChange;

  SetRelativeRotation(FRotator(0, Rotation, 0));
}

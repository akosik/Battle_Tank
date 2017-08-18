// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "GenericPlatformMath.h"
#include "TankWheel.h"

UTankWheel::UTankWheel()
{
  PrimaryComponentTick.bCanEverTick = true;

  // Check if get collisionshape works, it may give us a more accurate radius
  float CollisionRadius = GetCollisionShape().GetSphereRadius();
  if (CollisionRadius > 0.0f)
    Radius = CollisionRadius;
}

void UTankWheel::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  
  UpdateRotation(DeltaTime);
}

void UTankWheel::UpdateRotation(float DeltaTime)
{
  // We don't have to normalize by the vector projected onto bc the forward vector is already normalized
  float ForwardSpeed = FVector::DotProduct(GetOwner()->GetVelocity(), GetOwner()->GetActorForwardVector());
  float Pitch = FGenericPlatformMath::Fmod(ForwardSpeed * DeltaTime * 180.0f / 3.14f / Radius, 360.0f);
  AddLocalRotation(FRotator(-Pitch, 0, 0));
}

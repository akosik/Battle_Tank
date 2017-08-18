// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankWheel.h"
#include "TankMovementComponent.h"

UTankMovementComponent::UTankMovementComponent()
{ }

void UTankMovementComponent::InitializeMovementComponent(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
  LeftTrack = LeftTrackToSet;
  RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
  FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
  FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
  IntendMoveForward(FVector::DotProduct(AIForwardIntention,TankForward));
  IntendTurnRight(FVector::CrossProduct(TankForward, AIForwardIntention).Z);
}

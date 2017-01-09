// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
  PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
  Super::BeginPlay();
  OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
  DriveTrack();
  ApplySidewaysForce();
  CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
  float DeltaTime = GetWorld()->GetDeltaSeconds();
  float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetOwner()->GetVelocity());
  FVector CorrectiveAcceleration = - SlippageSpeed / DeltaTime * GetRightVector();
  UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>( GetOwner()->GetRootComponent() );
  FVector CorrectiveForce = CorrectiveAcceleration * TankRoot->GetMass() / 2; // Two tracks
  TankRoot->AddForce(CorrectiveForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
  CurrentThrottle =FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
  FVector ForceApplied = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
  FVector ForceLocation = GetComponentLocation();
  UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
  TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

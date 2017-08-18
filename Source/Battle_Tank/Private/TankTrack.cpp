// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "DrawDebugHelpers.h"
#include "GenericPlatformMath.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
  PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::InitializeTrack(UInstancedStaticMeshComponent* TileToSet, USplineComponent* SplineToSet, TArray<UTankWheel*> WheelsToSet)
{
  TrackTiles = TileToSet;
  TrackSpline = SplineToSet;
  Wheels = WheelsToSet;

  InstancingStep = TrackSpline->GetSplineLength() / TreadsPerTrack;
  InstanceTilesAlongTrack();
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  for(int i = 0; i < 8; ++i)
    DriveTrack(Wheels[i]);
  CurrentThrottle = 0;
  ApplySidewaysForce();
  UpdateTrackSpline(DeltaTime);
  UpdateTrackTiles(DeltaTime);
}

void UTankTrack::ApplySidewaysForce()
{
  float DeltaTime = GetWorld()->GetDeltaSeconds();
  float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetOwner()->GetVelocity());
  FVector CorrectiveAcceleration = - SlippageSpeed / DeltaTime * GetRightVector();
  UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>( GetOwner()->GetRootComponent() );
  FVector CorrectiveForce = CorrectiveAcceleration * TankRoot->GetMass() / 2; // Two tracks
  TankRoot->AddForce(CorrectiveForce * AntiSlippageCoefficient);
}

void UTankTrack::SetThrottle(float Throttle)
{
  CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack(UPrimitiveComponent* Wheel)
{
  FVector ForceApplied = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
  FVector ForceLocation = Wheel->GetComponentLocation();
  UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
  TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
  //DrawDebugLine(GetWorld(), ForceLocation, ForceLocation + ForceApplied, FColor::Blue, true);
}

void UTankTrack::UpdateTrackSpline(float DeltaTime)
{
  FVector Up = GetUpVector();
  for (int8 i = 1; i < 7; ++i)
    {
      FHitResult HitResult;
      FVector StartRay;
      FQuat Rotation;
      FVector PreviousWheelLocation = Wheels[i]->GetComponentLocation();
      Wheels[i]->GetAttachParent()->GetSocketWorldLocationAndRotation(Wheels[i]->GetAttachSocketName(), StartRay, Rotation);
      const FVector EndRay = StartRay - GetUpVector() * SuspensionLength;
      if (GetWorld()->SweepSingleByChannel(HitResult, StartRay, EndRay, Rotation, ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(Wheels[i]->Radius)) )
      	{
	  Wheels[i]->SetWorldLocation(HitResult.Location);
	  TrackSpline->SetLocationAtSplinePoint(i-1, HitResult.Location - Wheels[i]->Radius * Up, ESplineCoordinateSpace::World);
	  
	  const float DeltaSuspensionLocation = (FVector::DotProduct(HitResult.Location, Up) - FVector::DotProduct(PreviousWheelLocation, Up));
	  Wheels[i]->SuspensionCompressionLength = Wheels[i]->SuspensionCompressionLength + DeltaSuspensionLocation / SuspensionLength;	  
	  AddSuspensionForceForWheel(Wheels[i],  FVector::DotProduct(Wheels[i]->GetPhysicsLinearVelocity(), Up));
      	}
      else
      	{
      	  TrackSpline->SetLocationAtSplinePoint(i-1, EndRay - Wheels[i]->Radius * GetUpVector(), ESplineCoordinateSpace::World);
	  Wheels[i]->SetWorldLocation(EndRay);
	  Wheels[i]->SuspensionCompressionLength = 0;
      	}
    }

  // For Loop Close Point
  FHitResult HitResult;
  FVector StartRay;
  FQuat Rotation;
  Wheels[1]->GetAttachParent()->GetSocketWorldLocationAndRotation(Wheels[1]->GetAttachSocketName(), StartRay, Rotation);
  FVector EndRay = StartRay - GetUpVector() * SuspensionLength;
  if (GetWorld()->SweepSingleByChannel(HitResult, StartRay, EndRay, Rotation, ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(Wheels[1]->Radius)) )
    {
      TrackSpline->SetLocationAtSplinePoint(TrackSpline->GetNumberOfSplinePoints(), HitResult.ImpactPoint, ESplineCoordinateSpace::World);
    }
  else
    {
      TrackSpline->SetLocationAtSplinePoint(TrackSpline->GetNumberOfSplinePoints(), EndRay - Wheels[1]->Radius * Up, ESplineCoordinateSpace::World);
    }
  TrackSpline->UpdateSpline();
}

void UTankTrack::AddSuspensionForceForWheel(UTankWheel* Wheel, const float SuspensionSpeed)
{
  float DeltaTime = GetWorld()->GetDeltaSeconds();
  const float ShockForceMagnitude = -SuspensionSpeed * SuspensionDamping;
  const float SpringForceMagnitude = Wheel->SuspensionCompressionLength * SuspensionStiffness;
  UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
  const FVector ForceApplied = GetUpVector() * (ShockForceMagnitude + SpringForceMagnitude);
  const FVector ForceLocation = Wheel->GetComponentLocation();
  // DrawDebugLine(GetWorld(), ForceLocation, ForceLocation + GetUpVector() * ShockForceMagnitude, FColor::Red, false, -1, 0, 1.f);
  // DrawDebugLine(GetWorld(), ForceLocation, ForceLocation + GetUpVector() * SpringForceMagnitude, FColor::Green, false, -1, 0, 1.f);
  TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::InstanceTilesAlongTrack()
{
  static const FVector Scale(1);
  float DistanceAlongSpline = 0.0f;
  while (DistanceAlongSpline <= TrackSpline->GetSplineLength())
    {
      FRotator Rotation = TrackSpline->GetRotationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::Local);
      FVector Location = TrackSpline->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::Local);
      if (TrackSpline->GetRightVectorAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::Local).Y < 0)
	Rotation.Roll = FGenericPlatformMath::Fmod(Rotation.Roll + 180.0f, 360.0f);
      
      TrackTiles->AddInstance( FTransform(Rotation, Location, Scale) );

      DistanceAlongSpline += InstancingStep;
    }
  GetOwner()->UpdateComponentTransforms();
}

void UTankTrack::UpdateTrackTiles(float DeltaTime)
{
  static const FVector Scale(1);

  float ForwardSpeed = FVector::DotProduct(GetOwner()->GetVelocity(), GetForwardVector());
  TileDisplacementAlongSpline += ForwardSpeed * DeltaTime;
  TileDisplacementAlongSpline = FGenericPlatformMath::Fmod(TileDisplacementAlongSpline, TrackSpline->GetSplineLength());
  float DisplacedDistanceAlongSpline = TrackSpline->GetSplineLength() - TileDisplacementAlongSpline;
  
  for (int i = 0; i < TreadsPerTrack; ++i)
    {
      FRotator Rotation = TrackSpline->GetRotationAtDistanceAlongSpline(DisplacedDistanceAlongSpline, ESplineCoordinateSpace::Local);
      FVector Location = TrackSpline->GetLocationAtDistanceAlongSpline(DisplacedDistanceAlongSpline, ESplineCoordinateSpace::Local);
      if (TrackSpline->GetRightVectorAtDistanceAlongSpline(DisplacedDistanceAlongSpline, ESplineCoordinateSpace::Local).Y < 0.0f)
	Rotation.Roll = FGenericPlatformMath::Fmod(Rotation.Roll + 180.0f, 360.0f);

      FTransform UpdatedTransform(Rotation, Location, Scale);
      
      TrackTiles->UpdateInstanceTransform(i,
					  UpdatedTransform,
					  false,
					  i == TreadsPerTrack - 1 ? true : false,
					  false);
	
      DisplacedDistanceAlongSpline = CalculateWrappedTrackTileDistanceAlongSpline(DisplacedDistanceAlongSpline + InstancingStep);
    }
}

float UTankTrack::CalculateWrappedTrackTileDistanceAlongSpline(float UnwrappedDistance)
{
  float DisplacementModSplineLength = FGenericPlatformMath::Fmod(UnwrappedDistance, TrackSpline->GetSplineLength());
  if (DisplacementModSplineLength < 0.0f)
    {
      return TrackSpline->GetSplineLength() - DisplacementModSplineLength;
    }
  else
    {
      return DisplacementModSplineLength;
    }
}

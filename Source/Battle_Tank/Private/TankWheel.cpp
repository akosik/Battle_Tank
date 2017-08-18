// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "GenericPlatformMath.h"
#include "TankWheel.h"

UTankWheel::UTankWheel()
{
  PrimaryComponentTick.bCanEverTick = true;
}

void UTankWheel::BeginPlay()
{
  Super::BeginPlay();
  OnComponentHit.AddDynamic(this, &UTankWheel::OnHit);
}

void UTankWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
  UStaticMeshComponent* Tank = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
  VerticalAcceleration -= SuspensionCompressionLength * GetWorld()->GetDeltaSeconds() / Tank->GetMass();
  //AddSuspensionForceForWheel(Wheels[i], (GetComponentLocation() - StartRay).Size() / GetWorld()->GetDeltaSeconds());
}

void UTankWheel::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  
  //UpdateLocation(DeltaTime);
  UpdateRotation(DeltaTime);
  //UE_LOG(LogTemp, Warning, TEXT("NewLocation: %s, SocketLocation: %s, SuspensionCompressionLength: %f, Velocity: %f"), *(NewLocation.ToString()), *(SocketLocation.ToString()), SuspensionCompressionLength, VerticalVelocity);
}

void UTankWheel::UpdateRotation(float DeltaTime)
{
  // We don't have to normalize by the vector projected onto bc the forward vector is already normalized
  float ForwardSpeed = FVector::DotProduct(GetOwner()->GetVelocity(), GetOwner()->GetActorForwardVector());
  float Pitch = FGenericPlatformMath::Fmod(ForwardSpeed * DeltaTime * 180.0f / 3.14f / Radius, 360.0f);
  AddLocalRotation(FRotator(-Pitch, 0, 0));
}

void UTankWheel::UpdateLocation(float DeltaTime)
{
  // VerticalAcceleration += 980.0f;
  // VerticalVelocity += VerticalAcceleration * DeltaTime;
  // float SuspensionLength = 100.0f;
  // FVector PreviousWheelLocation = GetComponentLocation();
  // FVector SocketLocation = GetAttachParent()->GetSocketLocation(GetAttachSocketName());
  // FVector Up = GetOwner()->GetActorUpVector();
  // FVector NewLocation = PreviousWheelLocation + VerticalVelocity * DeltaTime * Up;
  // float NewDotUp = FVector::DotProduct(NewLocation, Up);
  // float SuspensionTopDotUp = FVector::DotProduct(SocketLocation, Up);
  // float SuspensionBottomDotUp = FVector::DotProduct(SocketLocation - SuspensionLength * Up, Up);
  
  // if (NewDotUp > SuspensionTopDotUp)
  //   {
  //     NewLocation = SocketLocation;
  //   }
  // else if (NewDotUp < SuspensionBottomDotUp)
  //   {
  //     NewLocation = SocketLocation - SuspensionLength * Up;
  //   }

  // SuspensionCompressionLength = FMath::Clamp<float>(NewLocation.Z - (SocketLocation.Z - SuspensionLength), 0.0f, SuspensionLength);
  // UE_LOG(LogTemp, Warning, TEXT("A: %f, V: %f, P: %f"), VerticalAcceleration, VerticalVelocity, SuspensionCompressionLength);
  // SetWorldLocation(NewLocation);
}

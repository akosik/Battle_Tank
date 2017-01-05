// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle_Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAt(FVector& HitLocation, float LaunchSpeed)
{
  if(!Barrel) { return; }
  FVector OutLaunchVelocity;
  FVector StartLocation = Barrel->GetSocketLocation(FName("FiringLocation"));
  if( UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace) )
    {
      FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
      UE_LOG(LogTemp, Warning, TEXT("Aiming at %s."), *AimDirection.ToString() );
    }
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
  Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
  // Find difference between aim direction and current direction
  FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
  FRotator AimAsRotator = AimDirection.Rotation();
  FRotator DeltaRotator = AimAsRotator - BarrelRotator;

  Barrel->Elevate(5);
}

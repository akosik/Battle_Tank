// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "DrawDebugHelpers.h"
#include "Tank.h"

ATank::ATank()
{ }

void ATank::BeginPlay()
{
  Super::BeginPlay();
  CurrentHealth = MaxHealth;

  // Lower Center Of Mass for Stability
  Cast<UPrimitiveComponent>(GetRootComponent())->SetCenterOfMass(CenterOfMass);

}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
  int32 DamageToApply = FMath::Clamp<float>(FPlatformMath::RoundToInt(DamageAmount), 0, CurrentHealth);
  CurrentHealth -= DamageToApply;
  if(CurrentHealth <= 0){ Die(); }
  return DamageToApply;
}

void ATank::Die()
{
  OnDeath.Broadcast();
  FTimerHandle TimerHandle;
  GetWorldTimerManager().SetTimer(TimerHandle, this, &ATank::DestroyTank, 3.f, false);
}

void ATank::DestroyTank()
{
  Destroy();
}

float ATank::GetHealthPercent() const
{
  return (float) CurrentHealth / (float) MaxHealth;
}

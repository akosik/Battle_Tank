// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
  Super::BeginPlay();
  CurrentHealth = MaxHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
  int32 DamageToApply = FMath::Clamp<float>(FPlatformMath::RoundToInt(DamageAmount), 0, CurrentHealth);
  CurrentHealth -= DamageToApply;
  if(CurrentHealth <= 0) { OnDeath.Broadcast(); }
  return DamageToApply;
}

float ATank::GetHealthPercent() const
{
  return (float) CurrentHealth / (float) MaxHealth;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "AzimuthElevationUserWidget.generated.h"

/**
 *
 */
UCLASS()
class BATTLE_TANK_API UAzimuthElevationUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
  UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);

};

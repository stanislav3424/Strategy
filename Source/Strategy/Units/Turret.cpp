// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "CommandComponent.h"

ATurret::ATurret()
{
    TurretCommandComponent = CreateDefaultSubobject<UTurretCommandComponent>(TEXT("TurretCommandComponent"));
}

UCommandComponent* ATurret::GetCommandComponent_Implementation()
{
    return TurretCommandComponent;
}
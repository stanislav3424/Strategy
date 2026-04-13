// Fill out your copyright notice in the Description page of Project Settings.

#include "Units/FactoryUnit.h"
#include "UnitFactoryComponent.h"

AFactoryUnit::AFactoryUnit()
{
    UnitFactoryComponent = CreateDefaultSubobject<UUnitFactoryComponent>(TEXT("UnitFactoryComponent"));
}
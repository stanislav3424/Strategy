// Fill out your copyright notice in the Description page of Project Settings.

#include "Units/FactoryUnit.h"
#include "UnitFactoryComponent.h"
#include "Components/SphereComponent.h"

AFactoryUnit::AFactoryUnit()
{
    UnitFactoryComponent = CreateDefaultSubobject<UUnitFactoryComponent>(TEXT("UnitFactoryComponent"));

    SpawnPoint = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnPoint"));
    SpawnPoint->SetupAttachment(GetRootComponent());
    SpawnPoint->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));
    SpawnPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    MovePoint = CreateDefaultSubobject<USphereComponent>(TEXT("MovePoint"));
    MovePoint->SetupAttachment(GetRootComponent());
    MovePoint->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));
    MovePoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnUnit.h"
#include "SpawnComponent.h"
#include "TeamComponent.h"
#include "ArmorComponent.h"

APawnUnit::APawnUnit()
{
    SpawnComponent        = CreateDefaultSubobject<USpawnComponent>(TEXT("SpawnComponent"));
    TeamComponent         = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
    ArmorComponent        = CreateDefaultSubobject<UArmorComponent>(TEXT("ArmorComponent"));

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void APawnUnit::BeginPlay()
{
    Super::BeginPlay();

}
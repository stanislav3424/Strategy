// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterUnit.h"
#include "SpawnComponent.h"
#include "TeamComponent.h"
#include "ArmorComponent.h"
#include "Turret.h"
#include "CommandComponent.h"

ACharacterUnit::ACharacterUnit()
{
    SpawnComponent        = CreateDefaultSubobject<USpawnComponent>(TEXT("SpawnComponent"));
    TeamComponent         = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
    ArmorComponent        = CreateDefaultSubobject<UArmorComponent>(TEXT("ArmorComponent"));
    UnitCommandComponent  = CreateDefaultSubobject<UUnitCommandComponent>(TEXT("UnitCommandComponent"));

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

UCommandComponent* ACharacterUnit::GetCommandComponent_Implementation()
{
    return UnitCommandComponent;
}

USpawnComponent* ACharacterUnit::GetSpawnComponent_Implementation()
{
    return SpawnComponent;
}

UTeamComponent* ACharacterUnit::GetTeamComponent_Implementation()
{
    return TeamComponent;
}

UArmorComponent* ACharacterUnit::GetArmorComponent_Implementation()
{
    return ArmorComponent;
}
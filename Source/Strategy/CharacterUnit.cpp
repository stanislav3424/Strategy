// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterUnit.h"
#include "SpawnComponent.h"
#include "TeamComponent.h"
#include "ArmorComponent.h"
#include "Components/ChildActorComponent.h"
#include "Turret.h"
#include "Commands/CommandComponent.h"

ACharacterUnit::ACharacterUnit()
{
    SpawnComponent        = CreateDefaultSubobject<USpawnComponent>(TEXT("SpawnComponent"));
    TeamComponent         = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
    ArmorComponent        = CreateDefaultSubobject<UArmorComponent>(TEXT("ArmorComponent"));
    UnitCommandComponent  = CreateDefaultSubobject<UUnitCommandComponent>(TEXT("UnitCommandComponent"));

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
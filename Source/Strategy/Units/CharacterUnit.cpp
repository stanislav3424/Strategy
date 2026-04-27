// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterUnit.h"
#include "UnitComponent/SpawnComponent.h"
#include "Team/TeamComponent.h"
#include "UnitComponent/ArmorComponent.h"
#include "Commands/AICommandQueueComponent.h"
#include "UnitComponent/SelectionComponent.h"

ACharacterUnit::ACharacterUnit()
{
    SpawnComponent          = CreateDefaultSubobject<USpawnComponent>(TEXT("SpawnComponent"));
    TeamComponent           = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
    ArmorComponent          = CreateDefaultSubobject<UArmorComponent>(TEXT("ArmorComponent"));
    AICommandQueueComponent = CreateDefaultSubobject<UAICommandQueueComponent>(TEXT("AICommandQueueComponent"));
    SelectionComponent      = CreateDefaultSubobject<USelectionComponent>(TEXT("SelectionComponent"));
    SelectionComponent->SetupAttachment(GetRootComponent());

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
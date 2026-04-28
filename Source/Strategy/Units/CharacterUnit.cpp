// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterUnit.h"
#include "Units/UnitComponent/SpawnComponent.h"
#include "Team/TeamComponent.h"
#include "Units/UnitComponent/ArmorComponent.h"
#include "Commands/AICommandQueueComponent.h"
#include "Units/UnitComponent/SelectionComponent.h"
#include "Units/UnitComponent/PathSplineComponent.h"

ACharacterUnit::ACharacterUnit()
{
    SpawnComponent          = CreateDefaultSubobject<USpawnComponent>(TEXT("SpawnComponent"));
    TeamComponent           = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
    ArmorComponent          = CreateDefaultSubobject<UArmorComponent>(TEXT("ArmorComponent"));
    AICommandQueueComponent = CreateDefaultSubobject<UAICommandQueueComponent>(TEXT("AICommandQueueComponent"));

    SelectionComponent = CreateDefaultSubobject<USelectionComponent>(TEXT("SelectionComponent"));
    SelectionComponent->SetupAttachment(GetRootComponent());

    PathSplineComponent = CreateDefaultSubobject<UPathSplineComponent>(TEXT("PathSplineComponent"));
    PathSplineComponent->SetupAttachment(GetRootComponent());
    PathSplineComponent->SetUsingAbsoluteLocation(true);
    PathSplineComponent->SetUsingAbsoluteRotation(true);
    PathSplineComponent->SetUsingAbsoluteScale(true);

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
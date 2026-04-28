// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnUnit.h"
#include "SpawnComponent.h"
#include "TeamComponent.h"
#include "ArmorComponent.h"
#include "AICommandQueueComponent.h"
#include "SelectionComponent.h"

APawnUnit::APawnUnit()
{
    auto RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    RootComponent           = RootSceneComponent;

    SpawnComponent          = CreateDefaultSubobject<USpawnComponent>(TEXT("SpawnComponent"));
    TeamComponent           = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
    ArmorComponent          = CreateDefaultSubobject<UArmorComponent>(TEXT("ArmorComponent"));
    AICommandQueueComponent = CreateDefaultSubobject<UAICommandQueueComponent>(TEXT("AICommandQueueComponent"));
    SelectionComponent      = CreateDefaultSubobject<USelectionComponent>(TEXT("SelectionComponent"));
    SelectionComponent->SetupAttachment(GetRootComponent());

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
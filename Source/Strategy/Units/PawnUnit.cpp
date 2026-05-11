// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnUnit.h"
#include "SpawnComponent.h"
#include "TeamComponent.h"
#include "ArmorComponent.h"
#include "AICommandQueueComponent.h"
#include "Units/UnitComponent/SelectionComponent.h"

APawnUnit::APawnUnit()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    SpawnComponent          = CreateDefaultSubobject<USpawnComponent>(TEXT("SpawnComponent"));
    TeamComponent           = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
    ArmorComponent          = CreateDefaultSubobject<UArmorComponent>(TEXT("ArmorComponent"));
    AICommandQueueComponent = CreateDefaultSubobject<UAICommandQueueComponent>(TEXT("AICommandQueueComponent"));
    SelectionComponent      = CreateDefaultSubobject<USelectionComponent>(TEXT("SelectionComponent"));
    PathSplineComponent     = CreateDefaultSubobject<UPathSplineComponent>(TEXT("PathSplineComponent"));

    SelectionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectionMesh"));
    SelectionMesh->SetupAttachment(GetRootComponent());
    SelectionMesh->bHiddenInSceneCapture = true;

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnUnit.h"
#include "SpawnComponent.h"
#include "TeamComponent.h"
#include "ArmorComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

APawnUnit::APawnUnit()
{
    SpawnComponent        = CreateDefaultSubobject<USpawnComponent>(TEXT("SpawnComponent"));
    TeamComponent         = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
    ArmorComponent        = CreateDefaultSubobject<UArmorComponent>(TEXT("ArmorComponent"));
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
    BlackboardComponent   = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    AutoPossessAI = EAutoPossessAI::Disabled;
}

void APawnUnit::BeginPlay()
{
    Super::BeginPlay();

}

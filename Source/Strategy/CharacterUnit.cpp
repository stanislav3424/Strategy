// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterUnit.h"
#include "SpawnComponent.h"
#include "TeamComponent.h"
#include "ArmorComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ACharacterUnit::ACharacterUnit()
{
	SpawnComponent = CreateDefaultSubobject<USpawnComponent>(TEXT("SpawnComponent"));
	TeamComponent = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
	ArmorComponent = CreateDefaultSubobject<UArmorComponent>(TEXT("ArmorComponent"));
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
    BlackboardComponent   = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    AutoPossessAI = EAutoPossessAI::Disabled;
}

void ACharacterUnit::CancelCommand()
{
}

void ACharacterUnit::CommandAttackUnit(AActor* TargetUnit)
{
}

void ACharacterUnit::CommandMoveTo(FVector const& Destination)
{
}

void ACharacterUnit::CommandAssault(FVector const& Destination)
{
}

void ACharacterUnit::BeginPlay()
{
	Super::BeginPlay();
	
	if (!BehaviorTreeComponent)
        return;

}




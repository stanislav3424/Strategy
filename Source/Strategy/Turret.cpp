// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void ATurret::CancelCommand()
{
    if (!BehaviorTreeComponent)
        return;
    if (BehaviorTrees.Contains(ETurretCommand::Default))
        BehaviorTreeComponent->StartTree(*BehaviorTrees[ETurretCommand::Default]);
    else
        UE_LOG(LogTemp, Error, TEXT("ATurret::CancelCommand - Turret %s does not have a default behavior tree set!"),
            *GetName());
}

void ATurret::CommandAttackUnit(AActor* TargetUnit)
{
    if (!BehaviorTreeComponent)
        return;

   if (BehaviorTrees.Contains(ETurretCommand::AttackUnit))
        BehaviorTreeComponent->StartTree(*BehaviorTrees[ETurretCommand::AttackUnit]);
    else
        UE_LOG(LogTemp, Error, TEXT("ATurret::CommandAttackUnit - Turret %s does not have an attack unit behavior tree set!"),
            *GetName());
}

void ATurret::BeginPlay()
{
    Super::BeginPlay();

    CancelCommand();
}

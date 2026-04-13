// Fill out your copyright notice in the Description page of Project Settings.

#include "CommandObject.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ComponentInterface.h"
#include "CommandComponent.h"

void UCommandObject::ExecuteCommand(AActor* Owner, FVector TargetLocation, AActor* TargetActor)
{
    if (!BehaviorTreeToExecute)
    {
        UE_LOG(
            LogTemp, Error, TEXT("UCommandObject::Execute - No BehaviorTreeToExecute set on Command %s!"), *GetName());
        return;
    }

    if (!Owner)
    {
        UE_LOG(LogTemp, Error, TEXT("UCommandObject::Execute - No Owner set on Command %s!"), *GetName());
        return;
    }

    auto AIController = Cast<AAIController>(Owner->GetInstigatorController());
    if (!AIController)
    {
        UE_LOG(LogTemp, Error, TEXT("UCommandObject::Execute - Owner %s does not have a valid AIController!"),
            *Owner->GetName());
        return;
    }

    AIController->RunBehaviorTree(BehaviorTreeToExecute);

    BlackboardComponent_Internal = AIController->GetBlackboardComponent();
    if (!BlackboardComponent_Internal)
    {
        UE_LOG(LogTemp, Error, TEXT("UCommandObject::Execute - Owner %s does not have a BlackboardComponent!"),
            *Owner->GetName());
        return;
    }

    Owner_Internal   = Owner;
    TargetLocation_Internal = TargetLocation;
    TargetActor_Internal = TargetActor; 

    OnExecuteeCommand(Owner, TargetLocation, TargetActor, BlackboardComponent_Internal);
}

void UCommandObject::EndExecution()
{
    OnEndExecution(Owner_Internal);

    if (!Owner_Internal || !BlackboardComponent_Internal)
        return;

    auto AIController = Cast<AAIController>(Owner_Internal->GetInstigatorController());
    if (!AIController)
        return;

    auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent());
    if (!BehaviorTreeComponent)
        return;

    BehaviorTreeComponent->StopTree();
}

TArray<UTurretCommandComponent*> UCommandObject::GetChildTurretCommandComponents(AActor* Owner)
{
    TArray<UTurretCommandComponent*> TurretCommandComponents;

    if (!Owner)
        return TurretCommandComponents;

    TArray<AActor*> ChildActors;
    Owner->GetAllChildActors(ChildActors);

    TurretCommandComponents.Reserve(ChildActors.Num());

    for (auto ChildActor : ChildActors)
    {
        if (!ChildActor)
            continue;

        if (!ChildActor->Implements<UComponentInterface>())
            continue;

        auto TurretCommandComponent =
            Cast<UTurretCommandComponent>(IComponentInterface::Execute_GetCommandComponent(ChildActor));
        if (!TurretCommandComponent)
            continue;

        TurretCommandComponents.Add(TurretCommandComponent);
    }

    return TurretCommandComponents;
}

void UUnitAttackUnitCommand::OnExecuteeCommand(
    AActor* Owner, FVector TargetLocation, AActor* TargetActor, UBlackboardComponent* BlackboardComponent)
{
    if (!Owner || !BlackboardComponent)
        return;

    if (!TargetActor)
    {
        UE_LOG(LogTemp, Error, TEXT("UUnitAttackUnitCommand::OnExecuteeCommand - No TargetActor provided for AttackUnit command!"));
        return;
    }

    BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), TargetActor);

    for (auto TurretCommandComponent : GetChildTurretCommandComponents(Owner))
    {
        if (!TurretCommandComponent)
            continue;
        TurretCommandComponent->CommandAttackUnit(TargetActor);
    }
}

void UUnitAttackUnitCommand::OnEndExecution(AActor* Owner)
{
    for (auto TurretCommandComponent : GetChildTurretCommandComponents(Owner))
    {
        if (!TurretCommandComponent)
            continue;
        TurretCommandComponent->CancelCommand();
    }
}

void UUnitMoveToCommand::OnExecuteeCommand(AActor* Owner, FVector TargetLocation, AActor* TargetActor, UBlackboardComponent* BlackboardComponent)
{
    if (!Owner || !BlackboardComponent)
        return;

    BlackboardComponent->SetValueAsVector(TEXT("TargetLocation"), TargetLocation);
}

void UUnitAssaultCommand::OnExecuteeCommand(AActor* Owner, FVector TargetLocation, AActor* TargetActor, UBlackboardComponent* BlackboardComponent)
{
    if (!Owner || !BlackboardComponent)
        return;

    BlackboardComponent->SetValueAsVector(TEXT("TargetLocation"), TargetLocation);
}

void UTurretAttackUnitCommand::OnExecuteeCommand(
    AActor* Owner, FVector TargetLocation, AActor* TargetActor, UBlackboardComponent* BlackboardComponent)
{
    if (!Owner || BlackboardComponent)
        return;

    if (!TargetActor)
    {
        UE_LOG(LogTemp, Error, TEXT("UTurretAttackUnitCommand::OnExecuteeCommand - No TargetActor provided for AttackUnit command!"));
        return;
    }

    BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), TargetActor);
}

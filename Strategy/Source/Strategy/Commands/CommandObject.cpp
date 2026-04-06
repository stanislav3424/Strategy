// Fill out your copyright notice in the Description page of Project Settings.

#include "CommandObject.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ComponentInterface.h"
#include "CommandComponent.h"

void UCommandObject::ExecuteCommand(AActor* Owner, UObject* Context)
{
    if (!BehaviorTreeToExecute)
    {
        UE_LOG(LogTemp, Error, TEXT("UCommandObject::Execute - No BehaviorTreeToExecute set on Command %s!"), *GetName());
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
        UE_LOG(LogTemp, Error, TEXT("UCommandObject::Execute - Owner %s does not have a valid AIController!"), *Owner->GetName());
        return;
    }

    AIController->RunBehaviorTree(BehaviorTreeToExecute);

    BlackboardComponent_Internal = AIController->GetBlackboardComponent();
    if (!BlackboardComponent_Internal)
    {
        UE_LOG(LogTemp, Error, TEXT("UCommandObject::Execute - Owner %s does not have a BlackboardComponent!"), *Owner->GetName());
        return;
    }

    Owner_Internal   = Owner;
    Context_Internal = Context;

    OnExecuteeCommand(Owner, Context, BlackboardComponent_Internal);
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
    AActor* Owner, UObject* Context, UBlackboardComponent* BlackboardComponent)
{
    if (!Owner || !Context || !BlackboardComponent)
        return;

    auto ActorContext = Cast<UActorContext>(Context);
    if (!ActorContext)
    {
        UE_LOG(LogTemp, Error,
            TEXT("UUnitAttackUnitCommand::OnExecuteeCommand - Context is not of type UActorContext!"));
        return;
    }

    BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), ActorContext->Actor);

    for (auto TurretCommandComponent : GetChildTurretCommandComponents(Owner))
    {
        if (!TurretCommandComponent)
            continue;
        TurretCommandComponent->CommandAttackUnit(ActorContext->Actor);
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

void UUnitMoveToCommand::OnExecuteeCommand(AActor* Owner, UObject* Context, UBlackboardComponent* BlackboardComponent)
{
    if (!Owner || !Context || !BlackboardComponent)
        return;

    auto VectorContext = Cast<UVectorContext>(Context);
    if (!VectorContext)
    {
        UE_LOG(
            LogTemp, Error, TEXT("UUnitMoveToCommand::OnExecuteeCommand - Context is not of type UVectorContext!"));
        return;
    }

    BlackboardComponent->SetValueAsVector(TEXT("TargetLocation"), VectorContext->Vector);
}

void UUnitAssaultCommand::OnExecuteeCommand(AActor* Owner, UObject* Context, UBlackboardComponent* BlackboardComponent)
{
    if (!Owner || !Context || !BlackboardComponent)
        return;

    auto VectorContext = Cast<UVectorContext>(Context);
    if (!VectorContext)
    {
        UE_LOG(
            LogTemp, Error, TEXT("UUnitAssaultCommand::OnExecuteeCommand - Context is not of type UVectorContext!"));
        return;
    }

    BlackboardComponent->SetValueAsVector(TEXT("TargetLocation"), VectorContext->Vector);
}

void UTurretAttackUnitCommand::OnExecuteeCommand(
    AActor* Owner, UObject* Context, UBlackboardComponent* BlackboardComponent)
{
    if (!Owner || !Context || !BlackboardComponent)
        return;

    auto ActorContext = Cast<UActorContext>(Context);
    if (!ActorContext)
    {
        UE_LOG(LogTemp, Error, TEXT("UTurretAttackUnitCommand::OnExecuteeCommand - Context is not of type UActorContext!"));
        return;
    }

    BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), ActorContext->Actor);
}

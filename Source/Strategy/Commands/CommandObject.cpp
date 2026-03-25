// Fill out your copyright notice in the Description page of Project Settings.

#include "Commands/CommandObject.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UCommandObject::ExecuteCommand(AActor* Owner, UObject* Context = nullptr)
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

    OnExecuteeCommand(Owner, Context, BlackboardComponent_Internal);
}

void UCommandObject::EndExecution()
{
    OnEndExecution();


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

    FVector TargetLocation = VectorContext->Vector;

    BlackboardComponent->SetValueAsVector(TEXT("TargetLocation"), TargetLocation);
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

    FVector TargetLocation = VectorContext->Vector;

    BlackboardComponent->SetValueAsVector(TEXT("TargetLocation"), TargetLocation);
}

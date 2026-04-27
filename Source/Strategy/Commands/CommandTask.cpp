// Fill out your copyright notice in the Description page of Project Settings.

#include "Commands/CommandTask.h"
#include "CheckFieldMacros.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UTexture2D* UCommandTask::GetCommandIcon() const
{
    CHECK_FIELD(LogTemp, CommandIcon);
    return CommandIcon;
}

void UCommandTask::RunTask()
{
    if (bIsRunning)
    {
        UE_LOG(LogTemp, Error, TEXT("UCommandTask::RunTask: Trying to run task %s that is already running"), *GetName());
        return;
    }

    bIsRunning = true;

    auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent());
    if (BehaviorTreeComponent)
        BehaviorTreeComponent->RestartTree(EBTRestartMode::CompleteRestart);

    CHECK_FIELD_RETURN(LogTemp, AIController);
    AIController->RunBehaviorTree(BehaviorTreeAsset);

    auto BlackboardComponent = AIController->GetBlackboardComponent();
    CHECK_FIELD_RETURN(LogTemp, BlackboardComponent);
    BlackboardComponent->SetValueAsObject("CommandTask", this);
    BlackboardComponent->SetValueAsVector("TargetLocation", TargetLocation);
    BlackboardComponent->SetValueAsObject("TargetActor", TargetActor);

    OnRunTask();
}

void UCommandTask::OnRunTask()
{
    

}

void UCommandTask::FinishTask()
{
    if (!bIsRunning)
        return;

    OnFinishTask();

    //CHECK_FIELD_RETURN(LogTemp, AIController);
    //auto BrainComponent = AIController->GetBrainComponent();
    //CHECK_FIELD_RETURN(LogTemp, BrainComponent);
    //BrainComponent->StopLogic("CommandTask finished");

    CHECK_FIELD_RETURN(LogTemp, AIController);
    auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent());  
    CHECK_FIELD_RETURN(LogTemp, BehaviorTreeComponent);
    BehaviorTreeComponent->StopTree(EBTStopMode::Forced);

    bIsRunning = false;
    OnTaskFinished.Broadcast(this);
}

void UCommandTask::OnFinishTask()
{
    
}

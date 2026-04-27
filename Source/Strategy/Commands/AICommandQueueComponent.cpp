// Fill out your copyright notice in the Description page of Project Settings.

#include "Commands/AICommandQueueComponent.h"
#include "Commands/CommandTask.h"
#include "CheckFieldMacros.h"
#include "GameplayTask.h"
#include "GameplayTasksComponent.h"
#include "GameplayTaskOwnerInterface.h"
#include "AIController.h"

void UAICommandQueueComponent::AddTask(TSubclassOf<UCommandTask> TaskClass, class AAIController* AIController, FVector TargetLocation, AActor* TargetActor)
{
    CHECK_FIELD_RETURN(LogTemp, TaskClass);

    UCommandTask* Task = NewObject<UCommandTask>(GetTransientPackage(), TaskClass);
    CHECK_FIELD_RETURN(LogTemp, Task);

    Task->SetAIController(AIController);
    Task->SetTargetLocation(TargetLocation);
    Task->SetTargetActor(TargetActor);

    Queue.Add(Task);
    TryStartNextTask();
}

void UAICommandQueueComponent::ClearQueue()
{
    Queue.Empty();

    EndCurrentTask();
}

void UAICommandQueueComponent::RemoveLastTask()
{

    if (Queue.IsEmpty())
        return;
    else
        Queue.Pop();

    if (Queue.IsEmpty())
        EndCurrentTask();
}

TArray<FVector> UAICommandQueueComponent::GetQueueTargetLocations() const
{
    TArray<FVector> Result;
    Result.Reserve(Queue.Num());
    for (const auto& Task : Queue)
        if (Task)
            Result.Add(Task->GetTargetLocation());
    return Result;
}

void UAICommandQueueComponent::BeginPlay()
{
    Super::BeginPlay();

    auto Owner = GetOwner();
    if (!Owner)
        return;
}

void UAICommandQueueComponent::TryStartNextTask()
{
    if (CurrentTask)
        return;

    if (Queue.IsEmpty())
        return;

    CurrentTask = Queue[0];

    if (!CurrentTask)
    {
        UE_LOG(LogTemp, Error, TEXT("CurrentTask is null for %s"), *GetOwner()->GetName());
        return;
    }

    CurrentTask->OnTaskFinished.AddDynamic(this, &UAICommandQueueComponent::OnTaskFinished);
    CurrentTask->RunTask();

}

void UAICommandQueueComponent::OnTaskFinished(UCommandTask* FinishedTask)
{
    if (!Queue.IsEmpty())
        Queue.RemoveAt(0);
    CurrentTask = nullptr;

    TryStartNextTask();
}

void UAICommandQueueComponent::EndCurrentTask()
{
    if (CurrentTask)
        CurrentTask->FinishTask();
}

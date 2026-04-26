// Fill out your copyright notice in the Description page of Project Settings.

#include "Commands/AICommandQueueComponent.h"
#include "Commands/CommandTask.h"
#include "CheckFieldMacros.h"
#include "GameplayTask.h"
#include "GameplayTasksComponent.h"
#include "GameplayTaskOwnerInterface.h"

void UAICommandQueueComponent::AddTask(TSubclassOf<UCommandTask> TaskClass, FVector TargetLocation, AActor* TargetActor)
{
    CHECK_FIELD_RETURN(LogTemp, TaskClass);
    auto Task = UGameplayTask::NewTask<UCommandTask>(*this);
    CHECK_FIELD_RETURN(LogTemp, Task);

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

    GameplayTasksComponent = Owner->FindComponentByClass<UGameplayTasksComponent>();
    CHECK_FIELD_RETURN(LogTemp, GameplayTasksComponent);

    if(AvailableTasks.IsEmpty())
        UE_LOG(LogTemp, Error, TEXT("No available tasks for %s"), *GetOwner()->GetName());
}

void UAICommandQueueComponent::TryStartNextTask()
{
    if (CurrentTask)
        return;

    if (!GameplayTasksComponent)
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
    UGameplayTasksComponent::RunGameplayTask(
        *GameplayTasksComponent, *CurrentTask, 0, FGameplayResourceSet(), FGameplayResourceSet());

}

void UAICommandQueueComponent::OnTaskFinished(UCommandTask* FinishedTask)
{
    EndCurrentTask();
    TryStartNextTask();
}

void UAICommandQueueComponent::EndCurrentTask()
{
    if (CurrentTask && CurrentTask->IsActive())
        CurrentTask->EndTask();

    Queue.RemoveAt(0);
    CurrentTask = nullptr;
}

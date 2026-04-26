// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AICommandQueueComponent.generated.h"

UCLASS(ClassGroup = (UnitComponent))
class UAICommandQueueComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void AddTask(TSubclassOf<class UCommandTask> TaskClass, FVector TargetLocation = FVector::ZeroVector,
        AActor* TargetActor = nullptr);

    UFUNCTION(BlueprintCallable)
    void ClearQueue();

    UFUNCTION(BlueprintCallable)
    void RemoveLastTask();

    UFUNCTION(BlueprintCallable)
    TArray<TSubclassOf<class UCommandTask>> GetAvailableTasks() const { return AvailableTasks; }

    UFUNCTION(BlueprintCallable)
    bool IsAvailableTask(TSubclassOf<class UCommandTask> TaskClass) const
    {
        return AvailableTasks.Contains(TaskClass);
    }

    UFUNCTION(BlueprintCallable)
    TArray<FVector> GetQueueTargetLocations() const;

    UFUNCTION(BlueprintCallable)
    TArray<class UCommandTask*> GetQueue() const { return Queue; };

protected:
    virtual void BeginPlay() override;
    void         TryStartNextTask();
    void         OnTaskFinished(class UCommandTask* FinishedTask);
    void         EndCurrentTask();

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    class UCommandTask* CurrentTask = nullptr;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    TArray<class UCommandTask*> Queue;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    class UGameplayTasksComponent* GameplayTasksComponent;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    TArray<TSubclassOf<class UCommandTask>> AvailableTasks;
};

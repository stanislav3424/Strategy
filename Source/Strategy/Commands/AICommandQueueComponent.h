// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AICommandQueueComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCommandQueueChanged);

UCLASS(ClassGroup = (UnitComponent))
class UAICommandQueueComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnCommandQueueChanged OnCommandQueueChanged;

    UFUNCTION(BlueprintCallable)
    static UAICommandQueueComponent* GetAICommandQueueComponent(AActor* Actor)
    {
        return Actor ? Actor->FindComponentByClass<UAICommandQueueComponent>() : nullptr;
    }

    UFUNCTION(BlueprintCallable)
    void AddTask(TSubclassOf<class UCommandTask> TaskClass, class AAIController* AIController,
        FVector TargetLocation = FVector::ZeroVector, AActor* TargetActor = nullptr);

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
    UFUNCTION()
    void         OnTaskFinished(class UCommandTask* FinishedTask);
    void         EndCurrentTask();

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    class UCommandTask* CurrentTask = nullptr;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    TArray<class UCommandTask*> Queue;

    UPROPERTY(EditDefaultsOnly, Category = "AvailableTasks")
    TArray<TSubclassOf<class UCommandTask>> AvailableTasks;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommandTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskFinished, UCommandTask*, Task);

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class STRATEGY_API UCommandTask : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnTaskFinished OnTaskFinished;

    UFUNCTION(BlueprintCallable)
    void SetAIController(AAIController* Controller) { AIController = Controller; }

    UFUNCTION(BlueprintCallable)
    void SetTargetLocation(FVector Location) { TargetLocation = Location; }

    UFUNCTION(BlueprintCallable)
    void SetTargetActor(AActor* Actor) { TargetActor = Actor; }

    UFUNCTION(BlueprintCallable)
    class AAIController* GetAIController() const { return AIController; }

    UFUNCTION(BlueprintCallable)
    FVector GetTargetLocation() const { return TargetLocation; }
    
    UFUNCTION(BlueprintCallable)
    AActor* GetTargetActor() const { return TargetActor; }
    
    UFUNCTION(BlueprintCallable, Category = "CommandInfo")
    UTexture2D* GetCommandIcon() const;

    UFUNCTION(BlueprintCallable, Category = "CommandInfo")
    FText GetCommandName() const { return CommandName; }

    UFUNCTION(BlueprintCallable)
    void RunTask();

    UFUNCTION(BlueprintCallable)
    void FinishTask();

    UFUNCTION(BlueprintCallable)
    bool IsRunning() const { return bIsRunning; }

protected:
    virtual void OnRunTask();
    virtual void OnFinishTask();

    UPROPERTY(EditDefaultsOnly, Category = "CommandInfo")
    UTexture2D* CommandIcon;

    UPROPERTY(EditDefaultsOnly, Category = "CommandInfo")
    FText CommandName;

    //UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command Info")
    //FText CommandDescription;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    class AAIController* AIController = nullptr;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    FVector TargetLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    AActor* TargetActor = nullptr;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    bool bIsRunning = false;

    UPROPERTY(EditDefaultsOnly, Category = "CommandInfo")
    class UBehaviorTree* BehaviorTreeAsset;
};

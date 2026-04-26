// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "CommandTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskFinished, UCommandTask*, Task);

/**
 * 
 */
UCLASS(NotBlueprintable, Abstract)
class STRATEGY_API UCommandTask : public UGameplayTask
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnTaskFinished OnTaskFinished;

    UFUNCTION(BlueprintCallable)
    void SetTargetLocation(FVector Location) { TargetLocation = Location; }

    UFUNCTION(BlueprintCallable)
    void SetTargetActor(AActor* Actor) { TargetActor = Actor; }

    UFUNCTION(BlueprintCallable)
    FVector GetTargetLocation() const { return TargetLocation; }
    
    UFUNCTION(BlueprintCallable)
    AActor* GetTargetActor() const { return TargetActor; }
    
    UFUNCTION(BlueprintCallable)
    UTexture2D* GetCommandIcon() const;
    
    UFUNCTION(BlueprintCallable)
    FText GetCommandName() const { return CommandName; }

protected:
    virtual void Activate() override;
    void         Finish();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command Info")
    UTexture2D* CommandIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command Info")
    FText CommandName;

    //UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command Info")
    //FText CommandDescription;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    FVector TargetLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    AActor* TargetActor = nullptr;
};

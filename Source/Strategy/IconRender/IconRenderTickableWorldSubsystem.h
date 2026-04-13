// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "IconRenderTickableWorldSubsystem.generated.h"

class UIconRenderSubsystem;

/**
 * 
 */
UCLASS()
class STRATEGY_API UIconRenderTickableWorldSubsystem : public UTickableWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(UIconRenderTickableWorldSubsystem, STATGROUP_Tickables);
    };

protected:
    virtual void OnWorldBeginPlay(UWorld& InWorld) override;

private:
    void OnWorldTick();

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    float TimeSinceLastTick = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    UIconRenderSubsystem* IconRenderSubsystem;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    float TickInterval = 1.0f;
};


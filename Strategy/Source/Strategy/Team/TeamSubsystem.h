// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TeamSubsystem.generated.h"

class UTeamState;
class UTeamComponent;

/**
 * 
 */
UCLASS()
class STRATEGY_API UTeamSubsystem : public UTickableWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void    Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(UTeamSubsystem, STATGROUP_Tickables);
    };
    UTeamState* GetTeamState(int32 TeamID);
    void        RegisterTeam(UTeamComponent* TeamComponent, int32 TeamID);
    void        UnregisterTeam(UTeamComponent* TeamComponent);

private:
    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TMap<int32, UTeamState*> TeamStates;
};

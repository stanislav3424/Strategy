// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TeamComponent.generated.h"


UCLASS(ClassGroup = (UnitComponent), meta = (BlueprintSpawnableComponent))
class STRATEGY_API UTeamComponent : public UActorComponent
{
    GENERATED_BODY()

    friend class UTeamSubsystem;

public:
    UTeamComponent();

    int32 GetTeamID() const { return TeamID; }
    void  SwitchTeamID(int32 InTeamID);
    bool  IsRegistered() const { return TeamID != INDEX_NONE; }

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "TeamID", meta = (AllowPrivateAccess = "true"))
    int32 TeamID = INDEX_NONE;
};

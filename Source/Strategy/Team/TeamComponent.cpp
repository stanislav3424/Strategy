// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamComponent.h"
#include "TeamSubsystem.h"

UTeamComponent::UTeamComponent()
{
}

void UTeamComponent::SwitchTeamID(int32 InTeamID)
{
    if (TeamID == InTeamID)
        return;

    if (InTeamID <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("UTeamComponent::SwitchTeamID - Invalid TeamID (%d) for %s"), InTeamID, *GetOwner()->GetName());
        return;
    }

    auto TeamSubsystem = UWorld::GetSubsystem<UTeamSubsystem>(GetWorld());
    if (!TeamSubsystem)
        return;

    TeamSubsystem->UnregisterTeam(this);
    TeamSubsystem->RegisterTeam(this, InTeamID);
}

void UTeamComponent::BeginPlay()
{
    Super::BeginPlay();

    auto World = GetWorld();
    if (!World)
        return;

    World->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda(
        [this]()
        {
            if (!IsValid(GetOwner()))
                return;

            if (TeamID <= 0)
            {
                UE_LOG(LogTemp, Error, TEXT("UTeamComponent::BeginPlay - TeamID is not set for %s"),
                    *GetOwner()->GetName());
                TeamID = INDEX_NONE;
                return;
            }

            auto TeamSubsystem = UWorld::GetSubsystem<UTeamSubsystem>(GetWorld());
            if (!TeamSubsystem)
                return;

            int32 InitTeamID = TeamID;
            TeamID           = INDEX_NONE;
            TeamSubsystem->RegisterTeam(this, InitTeamID);
        }));
}

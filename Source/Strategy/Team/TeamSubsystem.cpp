// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamSubsystem.h"
#include "TeamState.h"
#include "TeamComponent.h"

void UTeamSubsystem::Tick(float DeltaTime)
{
}

UTeamState* UTeamSubsystem::GetTeamState(int32 TeamID)
{
    auto TeamState = TeamStates.FindOrAdd(TeamID);
    if (!TeamState)
        TeamState = NewObject<UTeamState>(this);

    return TeamState;
}

void UTeamSubsystem::RegisterTeam(UTeamComponent* TeamComponent, int32 TeamID)
{
    if (!TeamComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("UTeamSubsystem::RegisterTeam - TeamComponent is null!"));
        return;
    }

    if (TeamComponent->IsRegistered())
    {
        UE_LOG(LogTemp, Error, TEXT("UTeamSubsystem::RegisterTeam - TeamComponent already has a TeamID!"));
        return;
    }

    auto TeamState = GetTeamState(TeamID);
    if (!TeamState)
        return;

    TeamState->RegisterTeamComponent(TeamComponent);

    TeamComponent->TeamID = TeamID;
}

void UTeamSubsystem::UnregisterTeam(UTeamComponent* TeamComponent)
{
    if (!TeamComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("UTeamSubsystem::UnregisterTeam - TeamComponent is null!"));
        return;
    }

    if (!TeamComponent->IsRegistered())
        return;

    auto TeamState = GetTeamState(TeamComponent->GetTeamID());
    if (!TeamState)
        return;

    TeamState->UnregisterTeamComponent(TeamComponent);

    TeamComponent->TeamID = INDEX_NONE;
}

TArray<AActor*> UTeamSubsystem::GetActorsInTeam(int32 TeamID, TArray<AActor*> Actors)
{
    TArray<AActor*> Restult;
    Restult.Reserve(Actors.Num());

    for (auto Actor : Actors)
    {
        if (!Actor)
            continue;
        auto TeamComponent = Actor->FindComponentByClass<UTeamComponent>();
        if (!TeamComponent)
            continue;
        if (TeamComponent->GetTeamID() == TeamID)
            Restult.Add(Actor);
    }

    return Restult;
}

int32 UTeamSubsystem::GetPlayerTeamID()
{
    return 1;
}

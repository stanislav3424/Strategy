// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamState.h"

void UTeamState::Tick(float DeltaTime)
{
    for (auto& ResourceData : Resources)
    {
        ResourceData.Value.Current += ResourceData.Value.DeltaPerSecond * DeltaTime;
    }
}

void UTeamState::RegisterTeamComponent(UTeamComponent* TeamComponent)
{
}

void UTeamState::UnregisterTeamComponent(UTeamComponent* TeamComponent)
{
}

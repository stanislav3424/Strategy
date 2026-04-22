// Fill out your copyright notice in the Description page of Project Settings.

#include "IconRenderTickableWorldSubsystem.h"
#include "IconRenderSubsystem.h"

void UIconRenderTickableWorldSubsystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!IconRenderSubsystem)
        return;

    TimeSinceLastTick += DeltaTime;

    if (TimeSinceLastTick >= TickInterval)
    {
        TimeSinceLastTick = 0.0f;
        IconRenderSubsystem->Tick();
    }

}

void UIconRenderTickableWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
    Super::OnWorldBeginPlay(InWorld);

    IconRenderSubsystem =
        UGameInstance::GetSubsystem<UIconRenderSubsystem>(InWorld.GetGameInstance());
}

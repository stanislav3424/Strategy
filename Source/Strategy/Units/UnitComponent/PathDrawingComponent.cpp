// Fill out your copyright notice in the Description page of Project Settings.

#include "PathDrawingComponent.h"
#include "Components/LineBatchComponent.h"
#include "Commands/AICommandQueueComponent.h"
#include "Engine/World.h"

UPathDrawingComponent::UPathDrawingComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UPathDrawingComponent::BeginPlay()
{
    Super::BeginPlay();

    auto Owner = GetOwner();
    if (Owner)
    {
        AICommandQueueComponent = Owner->FindComponentByClass<UAICommandQueueComponent>();
        if (AICommandQueueComponent)
        {
            AICommandQueueComponent->OnCommandQueueChanged.AddDynamic(this, &UPathDrawingComponent::UpdatePathPoints);
            UpdatePathPoints(); 
        }
    }
}

void UPathDrawingComponent::TickComponent(
    float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PathPoints.Num() < 2)
        return;

    UWorld* World = GetWorld();
    if (!World)
        return;

    ULineBatchComponent* LineBatcher = World->GetLineBatcher(UWorld::ELineBatcherType::Foreground);
    if (!LineBatcher)
        return;

    for (int32 i = 0; i < PathPoints.Num() - 1; ++i)
    {
        FVector Start = PathPoints[i];
        FVector End   = PathPoints[i + 1];

        if (PointOffset > 0.0f)
        {
            FVector Dir       = (End - Start).GetSafeNormal();
            float   SegLength = FVector::Dist(Start, End);
            float   Offset    = FMath::Min(PointOffset, SegLength * 0.5f);
            Start += Dir * Offset;
            End -= Dir * Offset;
        }

        LineBatcher->DrawLine(Start, End, LineColor, 0, LineThickness);

        if (i == PathPoints.Num() - 2)
        {
            LineBatcher->DrawDirectionalArrow(End, End * 0.0f, ArrowSize, LineColor, 0.f, 0, LineThickness);
        }
    }
}

void UPathDrawingComponent::UpdatePathPoints()
{
    PathPoints.Reset();

    if (!AICommandQueueComponent)
        return;

    auto Owner = GetOwner();
    if (!Owner)
        return;

    TArray<FVector> Targets = AICommandQueueComponent->GetQueueTargetLocations();
    PathPoints.Add(Owner->GetActorLocation());
    PathPoints.Append(Targets);
}

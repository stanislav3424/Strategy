// Fill out your copyright notice in the Description page of Project Settings.

#include "PathDrawingComponent.h"
#include "Components/LineBatchComponent.h"
#include "Commands/AICommandQueueComponent.h"
#include "NavigationSystem.h"
#include "Engine/World.h"

UPathDrawingComponent::UPathDrawingComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    CachedOwnerLocation               = FVector::ZeroVector;
}

void UPathDrawingComponent::BeginPlay()
{
    Super::BeginPlay();

    if (auto* Owner = GetOwner())
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

    if (auto* Owner = GetOwner())
    {
        FVector OwnerLoc = Owner->GetActorLocation();

        if (UWorld* World = GetWorld())
        {
            if (auto* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World))
            {
                FNavLocation NavLoc;
                if (NavSys->ProjectPointToNavigation(OwnerLoc, NavLoc))
                {
                    OwnerLoc = NavLoc.Location;
                }
            }
        }
        CachedOwnerLocation = OwnerLoc;
        PathPoints[0]       = OwnerLoc;
    }

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

        FVector Dir       = (End - Start).GetSafeNormal();
        float   SegLength = FVector::Dist(Start, End);
        float   Offset    = FMath::Min(PointOffset, SegLength * 0.5f);
        Start += Dir * Offset;
        End -= Dir * Offset;

        DrawSegment(Start, End, LineColor);
    }

    if (PathPoints.Num() > 0)
    {
        DrawTargetMarker(PathPoints.Last(), LineColor);
    }
}

void UPathDrawingComponent::UpdatePathPoints()
{
    PathPoints.Reset();

    if (!AICommandQueueComponent)
        return;

    auto* Owner = GetOwner();
    if (!Owner)
        return;

    TArray<FVector> Targets = AICommandQueueComponent->GetQueueTargetLocations();
    PathPoints.Add(Owner->GetActorLocation());
    PathPoints.Append(Targets);

    if (UWorld* World = GetWorld())
    {
        if (auto* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World))
        {
            FNavLocation NavLoc;
            if (NavSys->ProjectPointToNavigation(PathPoints[0], NavLoc))
            {
                PathPoints[0] = NavLoc.Location;
            }
        }
    }
    CachedOwnerLocation = PathPoints[0];
}

void UPathDrawingComponent::DrawSegment(const FVector& Start, const FVector& End, const FLinearColor& Color) const
{
    UWorld* World = GetWorld();
    if (!World)
        return;

    ULineBatchComponent* LineBatcher = World->GetLineBatcher(UWorld::ELineBatcherType::Foreground);
    if (!LineBatcher)
        return;

    FVector Dir    = (End - Start).GetSafeNormal();
    float   Length = FVector::Dist(Start, End);
    FVector Mid    = (Start + End) * 0.5f;

    FVector BoxExtent(Length * 0.5f, PathHalfWidth, PathHalfHeight);
    FBox    Box(-BoxExtent, BoxExtent);

    FRotator   Rot = Dir.Rotation();
    FTransform BoxTransform(Rot.Quaternion(), Mid);

    LineBatcher->DrawSolidBox(Box, BoxTransform, Color.ToFColor(false), SDPG_MAX, LineLifetime);
}

void UPathDrawingComponent::DrawTargetMarker(const FVector& Location, const FLinearColor& Color) const
{
    UWorld* World = GetWorld();
    if (!World)
        return;

    ULineBatchComponent* LineBatcher = World->GetLineBatcher(UWorld::ELineBatcherType::Foreground);
    if (!LineBatcher)
        return;

    FVector    Extent(TargetMarkerSize * 0.5f);
    FBox       Box(-Extent, Extent);
    FTransform T(Location);
    LineBatcher->DrawSolidBox(Box, T, Color.ToFColor(false), SDPG_MAX, LineLifetime);
}
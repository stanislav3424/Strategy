// Fill out your copyright notice in the Description page of Project Settings.

#include "Units/UnitComponent/PathSplineComponent.h"
#include "CheckFieldMacros.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Commands/AICommandQueueComponent.h"
#include "SelectionComponent.h"
#include "NavigationSystem.h"

UPathSplineComponent::UPathSplineComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    ClearSplinePoints(true);
}

void UPathSplineComponent::BeginPlay()
{
    Super::BeginPlay();

    CHECK_FIELD(LogTemp, SplinePointMiddleMesh);
    CHECK_FIELD(LogTemp, SplinePointEndMesh);
    CHECK_FIELD(LogTemp, SplinePointStartMesh);
    CHECK_FIELD(LogTemp, SplineMesh);

    ConstructSpline();

    auto Owner = GetOwner();
    if (!Owner)
        return;

    AICommandQueueComponent = Owner->FindComponentByClass<UAICommandQueueComponent>();
    CHECK_FIELD_RETURN(LogTemp, AICommandQueueComponent);
    SelectionComponent = Owner->FindComponentByClass<USelectionComponent>();
    CHECK_FIELD_RETURN(LogTemp, SelectionComponent);

    AICommandQueueComponent->OnCommandQueueChanged.AddDynamic(this, &UPathSplineComponent::UpdateSplinePointsInfo);
}

void UPathSplineComponent::TickComponent(
    float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // If less than 2 points, no need to update spline, just update owner location and return
    if (SplinePointsInfo.Num() < 2)
        return;

    UpdateOwnerLocation();
    ConstructSpline();
}

void UPathSplineComponent::UpdateOwnerLocation()
{
    auto Owner = GetOwner();
    if (!Owner)
        return;

    UWorld* World = GetWorld();
    if (!World)
        return;

    FVector OwnerLocation = Owner->GetActorLocation();

    auto NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
    if (NavigationSystem)
    {
        FNavLocation ProjectedLocation;
        if (NavigationSystem->ProjectPointToNavigation(OwnerLocation, ProjectedLocation))
            OwnerLocation = ProjectedLocation.Location;
    }

    if (!SplinePointsInfo.IsEmpty())
    {
        SplinePointsInfo[0].WorldLocation = OwnerLocation;
        SplinePointsInfo[0].bIsDirty      = true;
    }
}

void UPathSplineComponent::UpdateSplinePointsInfo()
{
    if (!AICommandQueueComponent)
        return;

    auto Owner = GetOwner();
    if (!Owner)
        return;

    auto TargetLocations = AICommandQueueComponent->GetQueueTargetLocations();
    TargetLocations.Insert(Owner->GetActorLocation(), 0);

    const int32 NewCount = TargetLocations.Num();
    const int32 OldCount = SplinePointsInfo.Num();

    if (OldCount > NewCount)
    {
        for (int32 Index = NewCount; Index < OldCount; ++Index)
        {
            auto& SplinePointInfo = SplinePointsInfo[Index];
            if (SplinePointInfo.PointMeshComponent)
            {
                SplinePointInfo.PointMeshComponent->DestroyComponent();
                SplinePointInfo.PointMeshComponent = nullptr;
            }
            if (SplinePointInfo.NextSegmentSplineMeshComponent)
            {
                SplinePointInfo.NextSegmentSplineMeshComponent->DestroyComponent();
                SplinePointInfo.NextSegmentSplineMeshComponent = nullptr;
            }
        }
        SplinePointsInfo.SetNum(NewCount);
    }
    else if (OldCount < NewCount)
    {
        SplinePointsInfo.AddDefaulted(NewCount - OldCount);
    }

    const int32 LastIndex = NewCount - 1;
    for (int32 Index = 0; Index < NewCount; ++Index)
    {
        SplinePointsInfo[Index].WorldLocation = TargetLocations[Index];

        if (Index == 0)
            SplinePointsInfo[Index].Type = ETypeSplinePoint::Start;
        else if (Index == LastIndex)
            SplinePointsInfo[Index].Type = ETypeSplinePoint::End;
        else
            SplinePointsInfo[Index].Type = ETypeSplinePoint::Middle;


        // Temporary
        SplinePointsInfo[Index].bIsDirty = true;
    }

    UpdateOwnerLocation();
    ConstructSpline();
}

void UPathSplineComponent::ConstructSpline()
{
    ClearSplinePoints(false);
    for (int32 Index = 0; Index < SplinePointsInfo.Num(); ++Index)
    {
        auto const& SplinePointInfo = SplinePointsInfo[Index];
        AddSplinePoint(SplinePointInfo.WorldLocation, ESplineCoordinateSpace::World, false);
        SetSplinePointType(Index, ESplinePointType::Linear, false);
    }
    UpdateSpline();

    ConstructSplineSegments();
}

void UPathSplineComponent::ConstructSplineSegments()
{
    // If less than 2 points, no need to construct segments, just clean up any existing mesh components
    if (SplinePointsInfo.Num() < 2)
    {
        for (auto& SplinePointInfo : SplinePointsInfo)
        {
            if (SplinePointInfo.PointMeshComponent)
            {
                SplinePointInfo.PointMeshComponent->DestroyComponent();
                SplinePointInfo.PointMeshComponent = nullptr;
            }
            if (SplinePointInfo.NextSegmentSplineMeshComponent)
            {
                SplinePointInfo.NextSegmentSplineMeshComponent->DestroyComponent();
                SplinePointInfo.NextSegmentSplineMeshComponent = nullptr;
            }
        }
        return;
    }

    // Otherwise, construct segments for all points
    for (int32 Index = 0; Index < SplinePointsInfo.Num(); ++Index)
        ConstructSplineSegment(Index);
}

void UPathSplineComponent::ConstructSplineSegment(int32 Index)
{
    if (!SplinePointsInfo.IsValidIndex(Index))
        return;

    // Check if this point or next segment is dirty, if not, skip
    bool  bIsNextSegmentDirty = false;
    auto& SplinePointInfo = SplinePointsInfo[Index];
    if (SplinePointsInfo.IsValidIndex(Index + 1))
        bIsNextSegmentDirty = SplinePointsInfo[Index + 1].bIsDirty;

    if (!SplinePointInfo.bIsDirty && !bIsNextSegmentDirty)
        return;

    // Construct PointMeshComponent
    if (!SplinePointInfo.PointMeshComponent)
    {
        SplinePointInfo.PointMeshComponent = NewObject<UStaticMeshComponent>(this);
        if (!SplinePointInfo.PointMeshComponent)
            return;
        SplinePointInfo.PointMeshComponent->SetMobility(EComponentMobility::Movable);
        SplinePointInfo.PointMeshComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
        SplinePointInfo.PointMeshComponent->RegisterComponent();
    }

    if (!SplinePointInfo.PointMeshComponent)
        return;

    // SetStaticMesh and WorldLocation
    switch (SplinePointInfo.Type)
    {
        case ETypeSplinePoint::Start:
            SplinePointInfo.PointMeshComponent->SetStaticMesh(SplinePointStartMesh);
            break;
        case ETypeSplinePoint::Middle:
            SplinePointInfo.PointMeshComponent->SetStaticMesh(SplinePointMiddleMesh);
            break;
        case ETypeSplinePoint::End:
            SplinePointInfo.PointMeshComponent->SetStaticMesh(SplinePointEndMesh);
            break;
        default:
            SplinePointInfo.PointMeshComponent->SetStaticMesh(nullptr);
            break;
    }

    SplinePointInfo.PointMeshComponent->SetWorldLocation(SplinePointInfo.WorldLocation);

    // NextSegmentSplineMeshComponent
    if (SplinePointInfo.Type != ETypeSplinePoint::End)
    {
        // Construct NextSegmentSplineMeshComponent
        if (!SplinePointInfo.NextSegmentSplineMeshComponent)
        {
            SplinePointInfo.NextSegmentSplineMeshComponent = NewObject<USplineMeshComponent>(this);
            if (!SplinePointInfo.NextSegmentSplineMeshComponent)
                return;

            SplinePointInfo.NextSegmentSplineMeshComponent->SetMobility(EComponentMobility::Movable);
            SplinePointInfo.NextSegmentSplineMeshComponent->AttachToComponent(
                this, FAttachmentTransformRules::KeepRelativeTransform);
            SplinePointInfo.NextSegmentSplineMeshComponent->RegisterComponent();
        }

        if (!SplinePointInfo.NextSegmentSplineMeshComponent)
            return;

        // SetStaticMesh and Start/End position & tangent
        int32 ThisIndex = Index;
        int32 NextIndex = Index + 1;
        float DistThis  = GetDistanceAlongSplineAtSplinePoint(ThisIndex);
        float DistNext  = GetDistanceAlongSplineAtSplinePoint(NextIndex);

        float SegmentLength = DistNext - DistThis;
        float Offset        = FMath::Min(SplineSegmentOffset, SegmentLength * 0.5f);

        if (Offset * 2.0f >= SegmentLength)
            return;

        // float Offset = 0.1f;

        float StartDist = DistThis + Offset;
        float EndDist   = DistNext - Offset;

        FVector StartPos = GetLocationAtDistanceAlongSpline(StartDist, ESplineCoordinateSpace::World);
        // FVector StartTangent = GetTangentAtDistanceAlongSpline(StartDist, ESplineCoordinateSpace::World);
        FVector EndPos = GetLocationAtDistanceAlongSpline(EndDist, ESplineCoordinateSpace::World);
        // FVector EndTangent   = GetTangentAtDistanceAlongSpline(EndDist, ESplineCoordinateSpace::World);
        FVector StartTangent = EndPos - StartPos;
        FVector EndTangent   = StartTangent;

        SplinePointInfo.NextSegmentSplineMeshComponent->SetStartAndEnd(
            StartPos, StartTangent, EndPos, EndTangent, true);

        SplinePointInfo.NextSegmentSplineMeshComponent->SetStaticMesh(SplineMesh);
    }
    else
    {
        // if last point, clear NextSegmentSplineMeshComponent
        if (SplinePointInfo.NextSegmentSplineMeshComponent)
            SplinePointInfo.NextSegmentSplineMeshComponent->SetStaticMesh(nullptr);
    }
}
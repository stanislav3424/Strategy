// Fill out your copyright notice in the Description page of Project Settings.

#include "Units/UnitComponent/PathSplineComponent.h"
#include "CheckFieldMacros.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Commands/AICommandQueueComponent.h"
#include "SelectionComponent.h"

UPathSplineComponent::UPathSplineComponent()
{
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
            auto& Info = SplinePointsInfo[Index];
            if (Info.PointMeshComponent)
            {
                Info.PointMeshComponent->DestroyComponent();
                Info.PointMeshComponent = nullptr;
            }
            if (Info.NextSegmentSplineMeshComponent)
            {
                Info.NextSegmentSplineMeshComponent->DestroyComponent();
                Info.NextSegmentSplineMeshComponent = nullptr;
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
    }

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

    for (int32 Index = 0; Index < SplinePointsInfo.Num(); ++Index)
    {
        if (!SplinePointsInfo.IsValidIndex(Index))
            break;

        auto& SplinePointInfo = SplinePointsInfo[Index];
        if (!SplinePointInfo.PointMeshComponent)
        {
            SplinePointInfo.PointMeshComponent = NewObject<UStaticMeshComponent>(this);
            if (!SplinePointInfo.PointMeshComponent)
                break;
            SplinePointInfo.PointMeshComponent->SetMobility(EComponentMobility::Movable);
            SplinePointInfo.PointMeshComponent->AttachToComponent(
                this, FAttachmentTransformRules::KeepRelativeTransform);
            SplinePointInfo.PointMeshComponent->RegisterComponent();
        }

        if (!SplinePointInfo.PointMeshComponent)
            break;

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

        if (SplinePointInfo.Type != ETypeSplinePoint::End)
        {
            if (!SplinePointInfo.NextSegmentSplineMeshComponent)
            {
                SplinePointInfo.NextSegmentSplineMeshComponent = NewObject<USplineMeshComponent>(this);
                if (!SplinePointInfo.NextSegmentSplineMeshComponent)
                    break;

                SplinePointInfo.NextSegmentSplineMeshComponent->SetMobility(EComponentMobility::Movable);
                SplinePointInfo.NextSegmentSplineMeshComponent->AttachToComponent(
                    this, FAttachmentTransformRules::KeepRelativeTransform);
                SplinePointInfo.NextSegmentSplineMeshComponent->RegisterComponent();
            }

            if (!SplinePointInfo.NextSegmentSplineMeshComponent)
                break;

            int32 ThisIndex = Index;
            int32 NextIndex = Index + 1;
            float DistThis  = GetDistanceAlongSplineAtSplinePoint(ThisIndex);
            float DistNext  = GetDistanceAlongSplineAtSplinePoint(NextIndex);

            float SegmentLength = DistNext - DistThis;
            float Offset        = FMath::Min(SplineSegmentOffset, SegmentLength * 0.5f);

            if (Offset * 2.0f >= SegmentLength)
                continue;

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

            if (SplineMesh)
            {
                SplinePointInfo.NextSegmentSplineMeshComponent->SetStaticMesh(SplineMesh);
                // SplinePointInfo.NextSegmentSplineMeshComponent->SetMaterial(0, SplineMesh->GetMaterial(0));
            }
        }
        else
        {
            if (SplinePointInfo.NextSegmentSplineMeshComponent)
                SplinePointInfo.NextSegmentSplineMeshComponent->SetStaticMesh(nullptr);
        }

    }
}

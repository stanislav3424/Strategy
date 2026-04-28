// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "PathSplineComponent.generated.h"

UENUM()
enum class ETypeSplinePoint : uint8
{
    None,
    Start,
    Middle,
    End,
};

USTRUCT(BlueprintType)
struct FSplinePointInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    ETypeSplinePoint Type = ETypeSplinePoint::None;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    FVector WorldLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    class UStaticMeshComponent* PointMeshComponent = nullptr;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    class USplineMeshComponent* NextSegmentSplineMeshComponent = nullptr;

    // UPROPERTY(BlueprintReadOnly, Category = "Debug")
    // FRotator Rotation = FRotator::ZeroRotator;
};

/**
 * 
 */
UCLASS(NotBlueprintable)
class STRATEGY_API UPathSplineComponent : public USplineComponent
{
    GENERATED_BODY()

public:
    UPathSplineComponent();

protected:
    virtual void BeginPlay() override;
    UFUNCTION()
    void         UpdateSplinePointsInfo();
    void         ConstructSpline();

    UPROPERTY(EditDefaultsOnly, Category = "SplineMesh")
    class UStaticMesh* SplinePointMiddleMesh;

    UPROPERTY(EditDefaultsOnly, Category = "SplineMesh")
    class UStaticMesh* SplinePointEndMesh;

    UPROPERTY(EditDefaultsOnly, Category = "SplineMesh")
    class UStaticMesh* SplinePointStartMesh;

    UPROPERTY(EditDefaultsOnly, Category = "SplineMesh")
    class UStaticMesh* SplineMesh;

private:
    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TArray<FSplinePointInfo> SplinePointsInfo;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    class UAICommandQueueComponent* AICommandQueueComponent;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    class USelectionComponent* SelectionComponent;
    
    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    float SplineSegmentOffset = 30.0f;
};

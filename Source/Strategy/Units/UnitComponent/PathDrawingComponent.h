// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PathDrawingComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STRATEGY_API UPathDrawingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPathDrawingComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(
        float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION()
    void UpdatePathPoints();

    void DrawSegment(const FVector& Start, const FVector& End, const FLinearColor& Color) const;

    void DrawTargetMarker(const FVector& Location, const FLinearColor& Color) const;

    UPROPERTY(EditAnywhere, Category = "Path Drawing")
    FLinearColor LineColor = FLinearColor::Green;

    UPROPERTY(EditAnywhere, Category = "Path Drawing")
    float PathHalfWidth = 25.0f;

    UPROPERTY(EditAnywhere, Category = "Path Drawing")
    float PathHalfHeight = 10.0f;

    UPROPERTY(EditAnywhere, Category = "Path Drawing")
    float TargetMarkerSize = 40.0f;

    UPROPERTY(EditAnywhere, Category = "Path Drawing")
    float PointOffset = 30.0f;

    UPROPERTY(EditAnywhere, Category = "Path Drawing")
    float LineLifetime = 0.0f;

private:
    TArray<FVector> PathPoints;

    UPROPERTY()
    class UAICommandQueueComponent* AICommandQueueComponent;

    FVector CachedOwnerLocation;
};
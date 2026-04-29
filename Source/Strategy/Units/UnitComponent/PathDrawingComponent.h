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

    UPROPERTY(EditDefaultsOnly, Category = "Path Drawing")
    FLinearColor LineColor = FLinearColor::Green;

    UPROPERTY(EditDefaultsOnly, Category = "Path Drawing")
    float LineThickness = 50.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Path Drawing")
    float ArrowSize = 20.0f; 

    UPROPERTY(EditDefaultsOnly, Category = "Path Drawing")
    float LineLifetime = 0.f; 

    UPROPERTY(EditDefaultsOnly, Category = "Path Drawing")
    float PointOffset = 30.0f; 

private:
    TArray<FVector> PathPoints;

    UPROPERTY()
    class UAICommandQueueComponent* AICommandQueueComponent;
};

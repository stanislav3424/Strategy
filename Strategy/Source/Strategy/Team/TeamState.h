// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TeamState.generated.h"

class UTeamComponent;

UENUM(BlueprintType)
enum class EResourceType : uint8
{
    Money,
};

USTRUCT(BlueprintType)
struct FResourceData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    float Current = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    float DeltaPerSecond = 0;
};

/**
 *
 */
UCLASS()
class STRATEGY_API UTeamState : public UObject
{
    GENERATED_BODY()

    friend class UTeamSubsystem;

public:
    float GetResourceCurrent(EResourceType ResourceType) const
    {
        if (auto const* ResourceData = Resources.Find(ResourceType))
            return ResourceData->Current;
        return 0;
    }
    float GetResourceDeltaPerSecond(EResourceType ResourceType) const
    {
        if (auto const* ResourceData = Resources.Find(ResourceType))
            return ResourceData->DeltaPerSecond;
        return 0;
    }

private:
    void Tick(float DeltaTime);

    void RegisterTeamComponent(UTeamComponent* TeamComponent);
    void UnregisterTeamComponent(UTeamComponent* TeamComponent);

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TMap<EResourceType, FResourceData> Resources;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TSet<UTeamComponent*> TeamComponents;
};

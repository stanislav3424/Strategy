// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnComponent.generated.h"


UCLASS(ClassGroup = (UnitComponent))
class STRATEGY_API USpawnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    float GetSpawnTime() const { return SpawnTime; }

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SpawnTime", meta = (AllowPrivateAccess = "true"))
    float SpawnTime = 1.f;
};

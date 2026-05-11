// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/PawnUnit.h"
#include "FactoryUnit.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class STRATEGY_API AFactoryUnit : public APawnUnit
{
    GENERATED_BODY()

public:
    AFactoryUnit();

    UFUNCTION(BlueprintCallable, Category = "UnitComponent")
    class UUnitFactoryComponent* GetUnitFactoryComponent() const { return UnitFactoryComponent; }

    UFUNCTION(BlueprintCallable, Category = "UnitComponent")
    class USphereComponent* GetSpawnPoint() const { return SpawnPoint; }

    UFUNCTION(BlueprintCallable, Category = "UnitComponent")
    class USphereComponent* GetMovePoint() const { return MovePoint; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UUnitFactoryComponent* UnitFactoryComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = "Unit Factory")
    class USphereComponent* SpawnPoint;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = "Unit Factory")
    class USphereComponent* MovePoint;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/PawnUnit.h"
#include "FactoryUnit.generated.h"

/**
 * 
 */
UCLASS()
class STRATEGY_API AFactoryUnit : public APawnUnit
{
	GENERATED_BODY()

public:
    AFactoryUnit();

    virtual class UUnitFactoryComponent* GetUnitFactoryComponent_Implementation() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UUnitFactoryComponent* UnitFactoryComponent;
};

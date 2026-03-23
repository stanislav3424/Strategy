// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnUnit.h"
#include "Turret.generated.h"

class UBehaviorTree;

UENUM(BlueprintType)
enum class ETurretCommand : uint8
{
    None,
    Default,
    AttackUnit,
};

/**
 * 
 */
UCLASS()
class STRATEGY_API ATurret : public APawnUnit
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Commands")
    void CancelCommand();

    UFUNCTION(BlueprintCallable, Category = "Commands")
    void CommandAttackUnit(AActor* TargetUnit);


protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    TMap<ETurretCommand, UBehaviorTree*> BehaviorTrees;
};

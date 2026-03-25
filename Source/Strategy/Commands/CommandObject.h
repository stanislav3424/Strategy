// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CommandObject.generated.h"

UCLASS(NotBlueprintable)
class STRATEGY_API UVectorContext : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    FVector Vector = FVector::ZeroVector;
};

UCLASS(Abstract, Blueprintable)
class STRATEGY_API UCommandObject : public UObject
{
    GENERATED_BODY()

public:
    void ExecuteCommand(AActor* Owner, UObject* Context = nullptr);
    void EndExecution();

protected:
    virtual void OnExecuteeCommand(
        AActor* Owner, UObject* Context, class UBlackboardComponent* BlackboardComponent) {};
    virtual void OnEndExecution() {};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
    class UBehaviorTree* BehaviorTreeToExecute;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    AActor* Owner_Internal;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    UObject* Context_Internal;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    FVector TargetLocation_Internal;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    class UBlackboardComponent* BlackboardComponent_Internal;
};

UCLASS(Abstract, Blueprintable)
class STRATEGY_API UUnitDefaultCommand : public UCommandObject
{
    GENERATED_BODY()

};

UCLASS(Abstract, Blueprintable)
class STRATEGY_API UUnitAttackUnitCommand : public UCommandObject
{
    GENERATED_BODY()
};

UCLASS(Abstract, Blueprintable)
class STRATEGY_API UUnitMoveToCommand : public UCommandObject
{
    GENERATED_BODY()

protected:
    virtual void OnExecuteeCommand(
        AActor* Owner, UObject* Context, class UBlackboardComponent* BlackboardComponent) override;
};

UCLASS(Abstract, Blueprintable)
class STRATEGY_API UUnitAssaultCommand : public UCommandObject
{
    GENERATED_BODY()

protected:
    virtual void OnExecuteeCommand(
        AActor* Owner, UObject* Context, class UBlackboardComponent* BlackboardComponent) override;
};

UCLASS(Abstract, Blueprintable)
class STRATEGY_API UTurretDefaultCommand : public UCommandObject
{
    GENERATED_BODY()
};

UCLASS(Abstract, Blueprintable)
class STRATEGY_API UTurretAttackUnitCommand : public UCommandObject
{
    GENERATED_BODY()
};

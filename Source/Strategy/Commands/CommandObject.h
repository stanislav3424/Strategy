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

UCLASS(NotBlueprintable)
class STRATEGY_API UActorContext : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    AActor* Actor = nullptr;
};

UCLASS(Abstract, Blueprintable)
class STRATEGY_API UCommandObject : public UObject
{
    GENERATED_BODY()

public:
    void ExecuteCommand(AActor* Owner, FVector TargetLocation = FVector::ZeroVector, AActor* TargetActor = nullptr);
    void EndExecution();
    static TArray<class UTurretCommandComponent*> GetChildTurretCommandComponents(AActor* Owner);
    class UTexture*                               GetIcon() const { return Icon; }

protected:
    virtual void OnExecuteeCommand(AActor* Owner, FVector TargetLocation,
        AActor* TargetActor, class UBlackboardComponent* BlackboardComponent) {};
    virtual void OnEndExecution(AActor* Owner) {};

    UPROPERTY(EditDefaultsOnly, Category = "BehaviorTree")
    class UBehaviorTree* BehaviorTreeToExecute;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    AActor* Owner_Internal;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    FVector TargetLocation_Internal;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    AActor* TargetActor_Internal;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    class UBlackboardComponent* BlackboardComponent_Internal;

    UPROPERTY(EditDefaultsOnly, Category = "Icon")
    class UTexture* Icon;
};

UCLASS(Abstract, Blueprintable)
class STRATEGY_API UUnitAttackUnitCommand : public UCommandObject
{
    GENERATED_BODY()

protected:
    virtual void OnExecuteeCommand(AActor* Owner, FVector TargetLocation,
        AActor* TargetActor, class UBlackboardComponent* BlackboardComponent) override;
    virtual void OnEndExecution(AActor* Owner) override;
};

UCLASS(Abstract, Blueprintable)
class STRATEGY_API UUnitMoveToCommand : public UCommandObject
{
    GENERATED_BODY()

protected:
    virtual void OnExecuteeCommand(AActor* Owner, FVector TargetLocation,
        AActor* TargetActor, class UBlackboardComponent* BlackboardComponent) override;
};

UCLASS(Abstract, Blueprintable)
class STRATEGY_API UUnitAssaultCommand : public UCommandObject
{
    GENERATED_BODY()

protected:
    virtual void OnExecuteeCommand(AActor* Owner, FVector TargetLocation,
        AActor* TargetActor, class UBlackboardComponent* BlackboardComponent) override;
};

UCLASS(Abstract, Blueprintable)
class STRATEGY_API UTurretAttackUnitCommand : public UCommandObject
{
    GENERATED_BODY()

protected:
    virtual void OnExecuteeCommand(
        AActor* Owner, FVector TargetLocation, AActor* TargetActor, class UBlackboardComponent* BlackboardComponent) override;
};

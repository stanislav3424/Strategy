// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CommandComponent.generated.h"

class UCommandObject;
class UBehaviorTreeComponent;

UCLASS(Abstract, ClassGroup = (UnitComponent))
class STRATEGY_API UCommandComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static UCommandComponent* GetCommandComponent(AActor* Actor);

    UFUNCTION(BlueprintCallable, Category = "Commands")
    void ExecuteCommand(TSubclassOf<UCommandObject> CommandClass, FVector TargetLocation = FVector::ZeroVector, AActor* TargetActor = nullptr);

    UFUNCTION(BlueprintCallable, Category = "Commands")
    virtual void CancelCommand();

    const TSet<TSubclassOf<UCommandObject>>& GetAvailableCommands() const { return AvailableCommands; }

protected:
    void ExecuteCommand(UCommandObject* Command, FVector TargetLocation = FVector::ZeroVector, AActor* TargetActor = nullptr);
    virtual void BeginPlay() override;
    bool         IsCurrentCommand(TSubclassOf<UCommandObject> CommandClass) const;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    TSet<TSubclassOf<UCommandObject>> AvailableCommands;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Commands")
    TSubclassOf<UCommandObject> DefaultCommand;

private:
    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    UCommandObject* CurrentCommand;
};

UCLASS(ClassGroup = (UnitComponent))
class STRATEGY_API UTurretCommandComponent : public UCommandComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Commands")
    void CommandAttackUnit(AActor* TargetUnit);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Commands")
    TSubclassOf<UCommandObject> AttackCommand;
};

UCLASS(ClassGroup = (UnitComponent))
class STRATEGY_API UUnitCommandComponent : public UCommandComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Commands")
    void CommandAttackUnit(AActor* TargetUnit);

    UFUNCTION(BlueprintCallable, Category = "Commands")
    void CommandMoveTo(FVector const& Destination);

    UFUNCTION(BlueprintCallable, Category = "Commands")
    void CommandAssault(FVector const& Destination);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Commands")
    TSubclassOf<UCommandObject> AttackCommand;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Commands")
    TSubclassOf<UCommandObject> MoveToCommand;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Commands")
    TSubclassOf<UCommandObject> AssaultCommand;
};

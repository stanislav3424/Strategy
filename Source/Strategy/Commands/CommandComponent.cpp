// Fill out your copyright notice in the Description page of Project Settings.

#include "Commands/CommandComponent.h"
#include "Commands/CommandObject.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

void UCommandComponent::BeginPlay()
{
    Super::BeginPlay();

    auto Owner = GetOwner();
    if (!Owner)
        return;

    if (!DefaultCommand)
    {
        UE_LOG(LogTemp, Error, TEXT("UCommandComponent::BeginPlay - No DefaultCommand set on CommandComponent of Owner %s!"),
            *Owner->GetName());
        return;
    }

    AvailableCommands.Add(DefaultCommand);
}

bool UCommandComponent::IsCurrentCommand(TSubclassOf<UCommandObject> CommandClass) const
{
    return CurrentCommand ? CurrentCommand->IsA(CommandClass) : false;
}

void UCommandComponent::ExecuteCommand(UCommandObject* Command, UObject* Context)
{
    if (!Command)
        return;

    if (IsCurrentCommand(Command->GetClass()))
        return;

    if (CurrentCommand)
        CurrentCommand->EndExecution();

    CurrentCommand = Command;
    if (!CurrentCommand)
        return;

    CurrentCommand->ExecuteCommand(GetOwner(), Context);
}

void UCommandComponent::CancelCommand()
{
    if (!DefaultCommand)
        return;

    auto Command = NewObject<UCommandObject>(this, DefaultCommand);
    if (!Command)
        return;

    ExecuteCommand(Command);
}

void UTurretCommandComponent::CommandAttackUnit(AActor* TargetUnit)
{
    if (!AttackCommand)
        return;

    auto Command = NewObject<UCommandObject>(this, AttackCommand);
    if (!Command)
        return;

    ExecuteCommand(Command);
}

void UTurretCommandComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!AttackCommand)
    {
        UE_LOG(LogTemp, Error, TEXT("UTurretCommandComponent::BeginPlay - No AttackCommand set on TurretCommandComponent of Owner %s!"),
            *GetOwner()->GetName());
        return;
    }
   
    AvailableCommands.Add(AttackCommand);

    CancelCommand();
}

void UUnitCommandComponent::CommandAttackUnit(AActor* TargetUnit)
{
    if (!AttackCommand)
        return;

    auto Command = NewObject<UCommandObject>(this, AttackCommand);
    if (!Command)
        return;

    ExecuteCommand(Command);
}

void UUnitCommandComponent::CommandMoveTo(FVector const& Destination)
{
    if (!MoveToCommand)
        return;

    auto Command = NewObject<UCommandObject>(this, MoveToCommand);
    if (!Command)
        return;

    auto Context = NewObject<UVectorContext>(Command);
    if (!Context)
        return;

    Context->Vector = Destination;

    ExecuteCommand(Command, Context);
}

void UUnitCommandComponent::CommandAssault(FVector const& Destination)
{
    if (!AssaultCommand)
        return;

    auto Command = NewObject<UCommandObject>(this, AssaultCommand);
    if (!Command)
        return;

    auto Context = NewObject<UVectorContext>(Command);
    if (!Context)
        return;

    Context->Vector = Destination;

    ExecuteCommand(Command, Context);
}

void UUnitCommandComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!AttackCommand)
    {
        UE_LOG(LogTemp, Error, TEXT("UUnitCommandComponent::BeginPlay - No AttackCommand set on UnitCommandComponent of Owner %s!"),
            *GetOwner()->GetName());
        return;
    }

    if (!MoveToCommand)
    {
        UE_LOG(LogTemp, Error, TEXT("UUnitCommandComponent::BeginPlay - No MoveToCommand set on UnitCommandComponent of Owner %s!"),
            *GetOwner()->GetName());
        return;
    }

    if (!AssaultCommand)
    {
        UE_LOG(LogTemp, Error, TEXT("UUnitCommandComponent::BeginPlay - No AssaultCommand set on UnitCommandComponent of Owner %s!"),
            *GetOwner()->GetName());
        return;
    }

    AvailableCommands.Add(AttackCommand);
    AvailableCommands.Add(MoveToCommand);
    AvailableCommands.Add(AssaultCommand);

    CancelCommand();
}

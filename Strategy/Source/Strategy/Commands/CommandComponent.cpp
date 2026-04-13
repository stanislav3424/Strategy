// Fill out your copyright notice in the Description page of Project Settings.

#include "CommandComponent.h"
#include "CommandObject.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "CheckFieldMacros.h"

void UCommandComponent::BeginPlay()
{
    Super::BeginPlay();

    CHECK_FIELD_RETURN(LogTemp, DefaultCommand);

    AvailableCommands.Add(DefaultCommand);

    CancelCommand();
}

bool UCommandComponent::IsCurrentCommand(TSubclassOf<UCommandObject> CommandClass) const
{
    return CurrentCommand ? CurrentCommand->IsA(CommandClass) : false;
}

void UCommandComponent::ExecuteCommand(UCommandObject* Command, FVector TargetLocation, AActor* TargetActor)
{
    if (!Command)
        return;

    if (CurrentCommand)
        CurrentCommand->EndExecution();

    CurrentCommand = Command;
    if (!CurrentCommand)
        return;

    CurrentCommand->ExecuteCommand(GetOwner(), TargetLocation, TargetActor);
}

UCommandComponent* UCommandComponent::GetCommandComponent(AActor* Actor)
{
    if (!Actor)
        return nullptr;

    if (auto Component = Actor->FindComponentByClass<UCommandComponent>())
        return Component;

    UE_LOG(LogTemp, Error, TEXT("UCommandComponent::GetCommandComponent - Actor %s does not have a CommandComponent!"),
        *Actor->GetName());

    return nullptr;
}

void UCommandComponent::ExecuteCommand(
    TSubclassOf<UCommandObject> CommandClass, FVector TargetLocation, AActor* TargetActor)
{
    if (!AvailableCommands.Contains(CommandClass))
        return;

    auto Command = NewObject<UCommandObject>(this, CommandClass);
    if (!Command)
        return;
    
    ExecuteCommand(Command, TargetLocation, TargetActor);
}

void UCommandComponent::CancelCommand()
{
    if (!DefaultCommand)
        return;

    ExecuteCommand(DefaultCommand);
}

void UTurretCommandComponent::CommandAttackUnit(AActor* TargetUnit)
{
    if (!AttackCommand)
        return;

    ExecuteCommand(DefaultCommand, FVector::ZeroVector, nullptr);
}

void UTurretCommandComponent::BeginPlay()
{
    Super::BeginPlay();

    CHECK_FIELD_RETURN(LogTemp, AttackCommand);
   
    AvailableCommands.Add(AttackCommand);

    CancelCommand();
}

void UUnitCommandComponent::CommandAttackUnit(AActor* TargetUnit)
{
    if (!AttackCommand)
        return;

    ExecuteCommand(AttackCommand, FVector::ZeroVector, TargetUnit);
}

void UUnitCommandComponent::CommandMoveTo(FVector const& Destination)
{
    if (!MoveToCommand)
        return;

    ExecuteCommand(MoveToCommand, Destination);
}

void UUnitCommandComponent::CommandAssault(FVector const& Destination)
{
    if (!AssaultCommand)
        return;

    ExecuteCommand(AssaultCommand, Destination);
}

void UUnitCommandComponent::BeginPlay()
{
    Super::BeginPlay();

    CHECK_FIELD_RETURN(LogTemp, AttackCommand);
    CHECK_FIELD_RETURN(LogTemp, MoveToCommand);
    CHECK_FIELD_RETURN(LogTemp, AssaultCommand);

    AvailableCommands.Add(AttackCommand);
    AvailableCommands.Add(MoveToCommand);
    AvailableCommands.Add(AssaultCommand);

    CancelCommand();
}

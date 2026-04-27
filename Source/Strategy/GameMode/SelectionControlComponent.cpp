// Fill out your copyright notice in the Description page of Project Settings.

#include "SelectionControlComponent.h"
#include "TeamSubsystem.h"
#include "SelectionComponent.h"
#include "CheckFieldMacros.h"
#include "EnhancedInputComponent.h"
#include "GamePlayerController.h"
#include "Commands/AICommandQueueComponent.h"
#include "Commands/CommandTask.h"
#include "AIController.h"

USelectionControlComponent::USelectionControlComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USelectionControlComponent::UpdateSelectionActors(TArray<AActor*> const& NewSelectedActors)
{

    // Unit selection
    TSet<AActor*> NewSelectedActorsSet;
    NewSelectedActorsSet.Append(UTeamSubsystem::GetActorsInTeam(UTeamSubsystem::GetPlayerTeamID(), NewSelectedActors));

    auto ActorsToDeselect = SelectedActors.Difference(NewSelectedActorsSet);
    auto ActorsToSelect   = NewSelectedActorsSet.Difference(SelectedActors);

    if (ActorsToDeselect.IsEmpty() && ActorsToSelect.IsEmpty())
        return;

    for (auto Actor : ActorsToDeselect)
        USelectionComponent::SetSelected(Actor, false);

    for (auto Actor : ActorsToSelect)
        USelectionComponent::SetSelected(Actor, true);

    SelectedActors = NewSelectedActorsSet;

    OnUpdateSelectedActors.Broadcast(SelectedActors.Array());

    // Commands
    TSet<TSubclassOf<UCommandTask>> NewAvailableCommandTasks;
    for (auto Actor : SelectedActors)
    {
        auto CommandComponent = Actor->FindComponentByClass<UAICommandQueueComponent>();
        if (!CommandComponent)
            continue;

        NewAvailableCommandTasks.Append(CommandComponent->GetAvailableTasks());
    }

    AvailableCommandTask              = NewAvailableCommandTasks;

    if (!AvailableCommandTask.Contains(CurrentCommandTask))
        CurrentCommandTask = nullptr;

    if (AvailableCommandTask.Array().IsValidIndex(0))
        CurrentCommandTask = AvailableCommandTask.Array()[0];

    OnUpdateAvailableCommandTasks.Broadcast(
        AvailableCommandTask.Array(), CurrentCommandTask);
}

AActor* USelectionControlComponent::GetActorUnderMouseCursor() const
{
    if (!PlayerController)
        return nullptr;
    FHitResult HitResult;
    PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
    return HitResult.GetActor();
}

void USelectionControlComponent::TickComponent(
    float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!PlayerController)
        return;

    EndSelectionLocation = AGamePlayerController::GetMouseWorldLocation(PlayerController);

    if (bIsDetectSelection)
    {
        FVector2D ScreenStart;
        PlayerController->ProjectWorldLocationToScreen(StartSelectionLocation, ScreenStart);
        FVector2D ScreenEnd;
        PlayerController->ProjectWorldLocationToScreen(EndSelectionLocation, ScreenEnd);

        if (FVector2D::DistSquared(ScreenStart, ScreenEnd) > DistanceThreshold * DistanceThreshold)
        {
            bIsSelection       = true;
            bIsDetectSelection = false;
        }
    }
}

void USelectionControlComponent::SelectionStarted()
{
    OnSelectionStarted(FInputActionValue());
}

void USelectionControlComponent::SelectionCompleted()
{
    OnSelectionCompleted(FInputActionValue());
}

void USelectionControlComponent::SetCurrentCommandTask(TSubclassOf<class UCommandTask> NewCommandTask)
{
    if (CurrentCommandTask == NewCommandTask)
        return;

    if (AvailableCommandTask.Contains(NewCommandTask))
        CurrentCommandTask = NewCommandTask;

     OnUpdateAvailableCommandTasks.Broadcast(AvailableCommandTask.Array(), CurrentCommandTask);
}

void USelectionControlComponent::OnSetupInputComponent(UEnhancedInputComponent* InputComponent)
{
    Super::OnSetupInputComponent(InputComponent);

    CHECK_FIELD_RETURN(LogTemp, SelectionAction);
    InputComponent->BindAction(
        SelectionAction, ETriggerEvent::Started, this, &USelectionControlComponent::OnSelectionStarted);
    InputComponent->BindAction(
        SelectionAction, ETriggerEvent::Completed, this, &USelectionControlComponent::OnSelectionCompleted);

    CHECK_FIELD_RETURN(LogTemp, CommandAction);
    InputComponent->BindAction(CommandAction, ETriggerEvent::Completed, this, &USelectionControlComponent::OnCommand);
}

void USelectionControlComponent::OnDeactivateInput()
{
    Super::OnDeactivateInput();

    bIsSelection       = false;
    bIsDetectSelection = false;

}

void USelectionControlComponent::OnSelectionStarted(FInputActionValue const& InputAction)
{
    bIsSelection       = false;
    bIsDetectSelection = true;

    StartSelectionLocation = AGamePlayerController::GetMouseWorldLocation(PlayerController);
    EndSelectionLocation   = StartSelectionLocation;
}

void USelectionControlComponent::OnSelectionCompleted(FInputActionValue const& InputAction)
{
    if (!bIsSelection && bIsDetectSelection)
    {
        TArray<AActor*> NewSelectedActors;
        NewSelectedActors.Add(GetActorUnderMouseCursor());
        UpdateSelectionActors(NewSelectedActors);
    }

    bIsSelection       = false;
    bIsDetectSelection = false;
}

void USelectionControlComponent::OnCommand(FInputActionValue const& InputAction)
{
    if (!PlayerController)
        return;

    if (!CurrentCommandTask)
        return;

    FHitResult HitResult;
    PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
    if (!HitResult.bBlockingHit)
        return;

    for (auto Actor : SelectedActors)
        if (auto AICommandQueueComponent = UAICommandQueueComponent::GetAICommandQueueComponent(Actor))
            AICommandQueueComponent->AddTask(CurrentCommandTask, Actor->GetInstigatorController<AAIController>(),
                HitResult.Location, HitResult.GetActor());
}
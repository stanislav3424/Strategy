// Fill out your copyright notice in the Description page of Project Settings.

#include "SelectionControlComponent.h"
#include "CommandComponent.h"
#include "TeamSubsystem.h"
#include "SelectionComponent.h"
#include "CheckFieldMacros.h"
#include "EnhancedInputComponent.h"
#include "GamePlayerController.h"

USelectionControlComponent::USelectionControlComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USelectionControlComponent::UpdateSelectionActors(TArray<AActor*> const& NewSelectedActors)
{
    TSet<AActor*> NewSelectedActorsSet;
    NewSelectedActorsSet.Append(UTeamSubsystem::GetActorsInTeam(UTeamSubsystem::GetPlayerTeamID(), NewSelectedActors));

    auto ActorsToDeselect = SelectedActors.Difference(NewSelectedActorsSet);
    auto ActorsToSelect   = NewSelectedActorsSet.Difference(SelectedActors);

    if (ActorsToDeselect.IsEmpty() && ActorsToSelect.IsEmpty())
        return;

    for (auto Actor : ActorsToDeselect)
    {
        USelectionComponent::SetSelected(Actor, false);
    }

    for (auto Actor : ActorsToSelect)
    {
        USelectionComponent::SetSelected(Actor, true);
    }

    SelectedActors = NewSelectedActorsSet;

    OnUpdateSelectedActors.Broadcast(SelectedActors.Array(), ActorsToDeselect.Array(), ActorsToSelect.Array());
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

    if (!CurrentCommand)
        return;

    FHitResult HitResult;
    PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
    if (!HitResult.bBlockingHit)
        return;

    for (auto Actor : SelectedActors)
        if (auto CommandComponent = UCommandComponent::GetCommandComponent(Actor))
            CommandComponent->ExecuteCommand(CurrentCommand, HitResult.Location, HitResult.GetActor());
}
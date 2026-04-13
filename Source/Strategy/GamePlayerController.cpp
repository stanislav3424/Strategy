// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayerController.h"
#include "TeamSubsystem.h"
#include "SelectionComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CheckFieldMacros.h"
#include "CommandComponent.h"

AGamePlayerController::AGamePlayerController()
{
    bShowMouseCursor = true;
}

void AGamePlayerController::UpdateSelectionActors(TArray<AActor*> const& NewSelectedActors)
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
}

AActor* AGamePlayerController::GetActorUnderMouseCursor() const
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
    return HitResult.GetActor();
}

FVector AGamePlayerController::GetMouseWorldLocation() const
{
    FHitResult HitResult;
    if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
        return HitResult.Location;
    if (DeprojectMousePositionToWorld(HitResult.Location, HitResult.ImpactNormal))
        return HitResult.Location;

    return HitResult.Location;
}

void AGamePlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    EndSelectionLocation = GetMouseWorldLocation();

    if (bIsDetectSelection)
    {
        FVector2D ScreenStart;
        ProjectWorldLocationToScreen(StartSelectionLocation, ScreenStart);
        FVector2D ScreenEnd;
        ProjectWorldLocationToScreen(EndSelectionLocation, ScreenEnd);

        if (FVector2D::DistSquared(ScreenStart, ScreenEnd) > DistanceThreshold * DistanceThreshold)
        {
            bIsSelection       = true;
            bIsDetectSelection = false;
        }
    }
}

void AGamePlayerController::BeginPlay()
{
    Super::BeginPlay();

    CHECK_FIELD_RETURN(LogTemp, DefaultMappingContext);

    auto LocalPlayer = GetLocalPlayer();
    if (!LocalPlayer)
        return;

    auto EnhancedInputLocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    if (!EnhancedInputLocalPlayerSubsystem)
        return;

    EnhancedInputLocalPlayerSubsystem->AddMappingContext(DefaultMappingContext, 0);
}

void AGamePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (!EnhancedInputComponent)
        return;

    CHECK_FIELD_RETURN(LogTemp, SelectionAction);
    EnhancedInputComponent->BindAction(
        SelectionAction, ETriggerEvent::Started, this, &AGamePlayerController::OnSelectionStarted);
    EnhancedInputComponent->BindAction(
        SelectionAction, ETriggerEvent::Completed, this, &AGamePlayerController::OnSelectionCompleted);


    CHECK_FIELD_RETURN(LogTemp, CommandAction);
    EnhancedInputComponent->BindAction(
        CommandAction, ETriggerEvent::Completed, this, &AGamePlayerController::OnCommand);
}

void AGamePlayerController::OnSelectionStarted(FInputActionValue const& InputAction)
{
    bIsSelection       = false;
    bIsDetectSelection = true;

    StartSelectionLocation = GetMouseWorldLocation();
    EndSelectionLocation   = StartSelectionLocation;
}

void AGamePlayerController::OnSelectionCompleted(FInputActionValue const& InputAction)
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

void AGamePlayerController::OnCommand(FInputActionValue const& InputAction)
{
    if (!CurrentCommand)
        return;

    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
    if (!HitResult.bBlockingHit)
        return;

    for (auto Actor : SelectedActors)
        if (auto CommandComponent = UCommandComponent::GetCommandComponent(Actor))
            CommandComponent->ExecuteCommand(CurrentCommand, HitResult.Location, HitResult.GetActor());
}

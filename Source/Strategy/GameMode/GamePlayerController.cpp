// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayerController.h"
#include "TeamSubsystem.h"
#include "SelectionComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CheckFieldMacros.h"
#include "SelectionControlComponent.h"
#include "BuildControlComponent.h"

AGamePlayerController::AGamePlayerController()
{
    bShowMouseCursor = true;

    SelectionControlComponent = CreateDefaultSubobject<USelectionControlComponent>(TEXT("SelectionControlComponent"));
    BuildControlComponent = CreateDefaultSubobject<UBuildControlComponent>(TEXT("BuildControlComponent"));

}

void AGamePlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

void AGamePlayerController::SetSelectionControl()
{
    if (CurrentControlComponent == SelectionControlComponent)
        return;

    if (CurrentControlComponent)
        CurrentControlComponent->DeactivateInput();

    CurrentControlComponent = SelectionControlComponent;
    if (CurrentControlComponent)
        CurrentControlComponent->ActivateInput();

    BroadcastSwitchControlComponent();
}

void AGamePlayerController::SetBuildControl()
{
    if (CurrentControlComponent == BuildControlComponent)
        return;

    if (CurrentControlComponent)
        CurrentControlComponent->DeactivateInput();

    CurrentControlComponent = BuildControlComponent;
    if (CurrentControlComponent)
        CurrentControlComponent->ActivateInput();

    BroadcastSwitchControlComponent();
}

void AGamePlayerController::SwitchControl()
{
    // Temporary
    if (CurrentControlComponent == BuildControlComponent)
        SetSelectionControl();
    else
        SetBuildControl();

    BroadcastSwitchControlComponent();
}

FVector AGamePlayerController::GetMouseWorldLocation(APlayerController* PlayerController)
{
    FHitResult HitResult;
    if (!PlayerController)
        return FVector::ZeroVector;
    if (PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
        return HitResult.Location;
    if (PlayerController->DeprojectMousePositionToWorld(HitResult.Location, HitResult.ImpactNormal))
        return HitResult.Location;

    return FVector::ZeroVector;
}

void AGamePlayerController::BroadcastSwitchControlComponent()
{
    OnSwitchControlComponent.Broadcast(CurrentControlComponent);
}

void AGamePlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetSelectionControl();

    auto LocalPlayer = GetLocalPlayer();
    CHECK_FIELD_RETURN(LogTemp, LocalPlayer);
    auto EnhancedInputLocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    CHECK_FIELD_RETURN(LogTemp, EnhancedInputLocalPlayerSubsystem);
    EnhancedInputLocalPlayerSubsystem->AddMappingContext(DefaultInputMappingContext, 0);
}

void AGamePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (!EnhancedInputComponent)
        return;

    CHECK_FIELD_RETURN(LogTemp, SelectionControlComponent);
    SelectionControlComponent->SetupInputComponent(EnhancedInputComponent);
    CHECK_FIELD_RETURN(LogTemp, BuildControlComponent);
    BuildControlComponent->SetupInputComponent(EnhancedInputComponent);

    EnhancedInputComponent->BindAction(
        SwitchControlAction, ETriggerEvent::Started, this, &AGamePlayerController::OnSwitchControl);
}

void AGamePlayerController::OnSwitchControl(FInputActionValue const& InputAction)
{
    SwitchControl();
}

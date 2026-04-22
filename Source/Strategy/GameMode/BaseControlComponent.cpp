// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseControlComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CheckFieldMacros.h"

void UBaseControlComponent::ActivateInput()
{
    CHECK_FIELD_RETURN(LogTemp, InputMappingContext);
    CHECK_FIELD_RETURN(LogTemp, EnhancedInputLocalPlayerSubsystem);
    EnhancedInputLocalPlayerSubsystem->AddMappingContext(InputMappingContext, 0);

    OnActivateInput();
}

void UBaseControlComponent::DeactivateInput()
{
    CHECK_FIELD_RETURN(LogTemp, InputMappingContext);
    CHECK_FIELD_RETURN(LogTemp, EnhancedInputLocalPlayerSubsystem);
    EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(InputMappingContext);

    OnDeactivateInput();
}

void UBaseControlComponent::SetupInputComponent(UEnhancedInputComponent* InputComponent)
{
    auto World = GetWorld();
    CHECK_FIELD_RETURN(LogTemp, World);
    auto LocalPlayer = World->GetFirstLocalPlayerFromController();
    CHECK_FIELD_RETURN(LogTemp, LocalPlayer);
    EnhancedInputLocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    CHECK_FIELD(LogTemp, EnhancedInputLocalPlayerSubsystem);

    PlayerController = Cast<APlayerController>(GetOwner());
    CHECK_FIELD(LogTemp, PlayerController);
    OnSetupInputComponent(InputComponent);
}


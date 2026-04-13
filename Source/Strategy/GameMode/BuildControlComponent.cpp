// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildControlComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CheckFieldMacros.h"

void UBuildControlComponent::OnSetupInputComponent(UEnhancedInputComponent* InputComponent)
{
    Super::OnSetupInputComponent(InputComponent);

    if (!InputComponent)
        return;

    CHECK_FIELD_RETURN(LogTemp, BuildAction);

}

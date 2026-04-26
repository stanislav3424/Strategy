// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInterface/BuildEntryWidget.h"
#include "CheckFieldMacros.h"
#include "GamePlayerController.h"

void UBuildEntryWidget::OnContextObjectSet(UObject* NewContextObject)
{
    Super::OnContextObjectSet(NewContextObject);
}

void UBuildEntryWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
    if (!bIsSelected)
        return;

    auto PlayerController = Cast<AGamePlayerController>(GetOwningPlayer());
    if (!PlayerController)
        return;

    //auto SelectionControlComponent = PlayerController->FindComponentByClass<USelectionControlComponent>();
    //if (!SelectionControlComponent)
    //    return;

    //if (ContextObject)
    //    SelectionControlComponent->SetCurrentCommand(ContextObject->GetClass());
}

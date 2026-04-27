// Fill out your copyright notice in the Description page of Project Settings.

#include "CommandEntryWidget.h"
#include "Commands/CommandTask.h"
#include "CheckFieldMacros.h"
#include "GamePlayerController.h"
#include "SelectionControlComponent.h"

void UCommandEntryWidget::OnContextObjectSet(UObject* NewContextObject)
{
    CHECK_FIELD_RETURN(LogTemp, NewContextObject);
    auto CommandClass = Cast<UClass>(NewContextObject);
    CHECK_FIELD_RETURN(LogTemp, CommandClass);
    auto CommandTask  = NewObject<UCommandTask>(this, CommandClass);
    CHECK_FIELD_RETURN(LogTemp, CommandTask);

    auto Icon = CommandTask->GetCommandIcon();
    CHECK_FIELD_RETURN(LogTemp, Icon);

    // override
    ChildContextObjectSet(Icon);
    UpdateAllConstructs();
}

void UCommandEntryWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
    if (!bIsSelected)
        return;

    auto PlayerController = Cast<AGamePlayerController>(GetOwningPlayer());
    if (!PlayerController)
        return;

    auto SelectionControlComponent = PlayerController->FindComponentByClass<USelectionControlComponent>();
    if (!SelectionControlComponent)
        return;

    if (ContextObject)
        SelectionControlComponent->SetCurrentCommandTask(ContextObject->GetClass());
}

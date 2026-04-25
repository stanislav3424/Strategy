// Fill out your copyright notice in the Description page of Project Settings.

#include "CommandEntryWidget.h"
#include "CommandObject.h"
#include "CheckFieldMacros.h"
#include "GamePlayerController.h"
#include "SelectionControlComponent.h"

void UCommandEntryWidget::OnContextObjectSet(UObject* NewContextObject)
{
    CHECK_FIELD_RETURN(LogTemp, NewContextObject);
    auto CommandObject = Cast<UCommandObject>(NewContextObject);
    CHECK_FIELD_RETURN(LogTemp, CommandObject);

    auto Icon = CommandObject->GetIcon();
    CHECK_FIELD_RETURN(LogTemp, Icon);

    // override 
    ChildContextObjectSet(Icon);
    UpdateAllConstructs();
}

//FReply UCommandEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//    auto PlayerController = Cast<AGamePlayerController>(GetOwningPlayer());
//    if (!PlayerController)
//        return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
//
//    auto SelectionControlComponent = PlayerController->FindComponentByClass<USelectionControlComponent>();
//    if (!SelectionControlComponent)
//        return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
//
//    if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
//    {
//        if (ContextObject)
//            SelectionControlComponent->SetCurrentCommand(ContextObject->GetClass());
//        return FReply::Handled();
//    }
//
//    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
//}

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
        SelectionControlComponent->SetCurrentCommand(ContextObject->GetClass());

    //UpdateAllConstructs();
}

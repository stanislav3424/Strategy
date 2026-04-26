// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInterface/UnitEntryWidget.h"
#include "IconRenderLibrary.h"
#include "Components/Image.h"
#include "CheckFieldMacros.h"
#include "GamePlayerController.h"
#include "SelectionControlComponent.h"

void UUnitEntryWidget::OnContextObjectSet(UObject* NewContextObject)
{
    ChildContextObjectSet(GetUnitClass());
    UpdateAllConstructs();
}

FReply UUnitEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    auto PlayerController = Cast<AGamePlayerController>(GetOwningPlayer());
    if (!PlayerController)
        return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    auto SelectionControlComponent = PlayerController->FindComponentByClass<USelectionControlComponent>();
    if (!SelectionControlComponent)
        return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
    {
        SelectionControlComponent->UpdateSelectionActors(GetUnits());
        return FReply::Handled();
    }
    if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
    {
        //SelectionControlComponent->UpdateSelectionActors(GetUnits());
        return FReply::Handled();
    }

    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

TSubclassOf<AActor> UUnitEntryWidget::GetUnitClass() const
{
    auto UnitEntryObject = Cast<UUnitEntryObject>(GetListItem());
    if (!UnitEntryObject)
        return nullptr;

    return UnitEntryObject->UnitClass;
}

int32 UUnitEntryWidget::GetNumUnits() const
{
    auto UnitEntryObject = Cast<UUnitEntryObject>(GetListItem());
    if (!UnitEntryObject)
        return 0;

    return UnitEntryObject->NumUnits;
}

TArray<AActor*> UUnitEntryWidget::GetUnits() const
{
    auto UnitEntryObject = Cast<UUnitEntryObject>(GetListItem());
    if (!UnitEntryObject)
        return TArray<AActor*>();

    return UnitEntryObject->Units;
}

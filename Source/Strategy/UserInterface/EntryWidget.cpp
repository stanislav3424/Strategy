// Fill out your copyright notice in the Description page of Project Settings.

#include "EntryWidget.h"
#include "IconRenderLibrary.h"
#include "Components/Image.h"
#include "CheckFieldMacros.h"

void UEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    SetContext(ListItemObject);
}

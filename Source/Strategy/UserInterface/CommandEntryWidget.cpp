// Fill out your copyright notice in the Description page of Project Settings.

#include "CommandEntryWidget.h"
#include "CommandObject.h"
#include "CheckFieldMacros.h"

void UCommandEntryWidget::OnContextObjectSet(UObject* NewContextObject)
{
    CHECK_FIELD_RETURN(LogTemp, NewContextObject);
    auto CommandObject = Cast<UCommandObject>(NewContextObject);
    CHECK_FIELD_RETURN(LogTemp, CommandObject);

    auto Icon = CommandObject->GetIcon();
    CHECK_FIELD_RETURN(LogTemp, Icon);

    ChildContextObjectSet(Icon);
}

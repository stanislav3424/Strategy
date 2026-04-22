// Fill out your copyright notice in the Description page of Project Settings.

#include "ContextWidget.h"
#include "Blueprint/WidgetTree.h"

void UContextWidget::ContextObjectSet(UObject* NewContextObject)
{
    if (ContextObject == NewContextObject)
        return;

    ContextObject = NewContextObject;

    OnContextObjectSet(NewContextObject);
}

void UContextWidget::OnContextObjectSet(UObject* NewContextObject)
{
    ChildContextObjectSet();
}

void UContextWidget::ChildContextObjectSet()
{
    if (!ContextObject)
        return;

    if (!WidgetTree)
        return;

    TArray<UWidget*> Childrens;
    WidgetTree->GetChildWidgets(this->GetRootWidget(), Childrens);
    for (auto Children : Childrens)
        if (auto ContextWidget = Cast<UContextWidget>(Children))
            ContextWidget->ContextObjectSet(ContextObject);
}

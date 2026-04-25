// Fill out your copyright notice in the Description page of Project Settings.

#include "ContextWidget.h"
#include "Blueprint/WidgetTree.h"

void UContextWidget::SetContext(UObject* NewContextObject)
{
    if (ContextObject == NewContextObject)
        return;

    ContextObject = NewContextObject;

    OnContextObjectSet(NewContextObject);
}

void UContextWidget::OnContextObjectSet(UObject* NewContextObject)
{
    ChildContextObjectSet(NewContextObject);

    UpdateAllConstructs();
}

void UContextWidget::ChildContextObjectSet(UObject* NewContextObject)
{
    if (!NewContextObject)
        return;

    if (!WidgetTree)
        return;

    TArray<UWidget*> Childrens;
    WidgetTree->GetChildWidgets(this->GetRootWidget(), Childrens);
    for (auto Children : Childrens)
        if (auto ContextWidget = Cast<UContextWidget>(Children))
            ContextWidget->SetContext(NewContextObject);
}

void UContextWidget::UpdateAllConstructs()
{
    NativePreConstruct();
    NativeConstruct();
    PreConstruct(false);
    Construct();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/IconWidget.h"
#include "Components/Image.h"

void UIconWidget::OnContextObjectSet(UObject* NewContextObject)
{
    Super::OnContextObjectSet(NewContextObject);

    // Temporely
    if (!Icon)
        return;

    auto ContextTexture = Cast<UTexture2D>(NewContextObject);
    if (!ContextTexture)
        return;
    Icon->SetBrushFromTexture(ContextTexture);
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "IconWidget.h"
#include "IconRenderLibrary.h"
#include "Components/Image.h"
#include "CheckFieldMacros.h"

void UIconWidget::OnContextObjectSet(UObject* NewContextObject)
{
    Super::OnContextObjectSet(NewContextObject);

    CHECK_FIELD_RETURN(LogTemp, IconRenderActorClass);

    auto Actor = Cast<AActor>(NewContextObject);
    CHECK_FIELD_RETURN(LogTemp, Actor);

    FOnIconReady IconReadyDelegate;
    IconReadyDelegate.BindDynamic(this, &UIconWidget::OnIconReady);

    UIconRenderLibrary::RequestIcon(this, IconRenderActorClass, Actor->GetClass(), IconReadyDelegate);
}

void UIconWidget::OnIconReady(UTexture* Icon)
{
    if (!UnitIcon)
        return;

    CHECK_FIELD_RETURN(LogTemp, Icon);

    auto DynamicMaterial = UnitIcon->GetDynamicMaterial();
    CHECK_FIELD_RETURN(LogTemp, DynamicMaterial);

    DynamicMaterial->SetTextureParameterValue(TEXT("Icon"), Icon);
    DynamicMaterial->SetScalarParameterValue(TEXT("IsLoading"), 0.f);
}

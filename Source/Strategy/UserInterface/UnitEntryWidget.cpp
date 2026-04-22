// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInterface/UnitEntryWidget.h"
#include "IconRenderLibrary.h"
#include "Components/Image.h"
#include "CheckFieldMacros.h"

void UUnitEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{ 
	auto Actor =Cast<AActor>(ListItemObject);
    if (!Actor)
        return;

    FOnIconReady IconReadyDelegate;
    IconReadyDelegate.BindDynamic(this, &UUnitEntryWidget::OnIconReady);

    UIconRenderLibrary::RequestIcon(this, IconRenderActorClass, Actor->GetClass(), IconReadyDelegate);
}

void UUnitEntryWidget::OnIconReady(UTexture* Icon)
{
    UE_LOG(LogTemp, Error, TEXT("UUnitEntryWidget::OnIconReady - Icon is ready"));

    if (!UnitIcon)
        return;

    CHECK_FIELD_RETURN(LogTemp, Icon);

    auto DynamicMaterial = UnitIcon->GetDynamicMaterial();
    CHECK_FIELD_RETURN(LogTemp, DynamicMaterial);

    DynamicMaterial->SetTextureParameterValue(TEXT("Icon"), Icon);
}

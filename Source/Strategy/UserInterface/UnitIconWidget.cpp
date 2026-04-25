// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitIconWidget.h"
#include "IconRenderLibrary.h"
#include "Components/Image.h"
#include "CheckFieldMacros.h"

void UUnitIconWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    // Reset the icon to a loading state
    auto DynamicMaterial = UnitIcon->GetDynamicMaterial();
    CHECK_FIELD_RETURN(LogTemp, DynamicMaterial);
    DynamicMaterial->SetScalarParameterValue(TEXT("IsLoading"), 1.f);

    // UUnitIconWidget::OnIconReady int32 RequestId = 0 synchronous 
    CurrentRequestId = 0;

    if (!ContextObject)
        return;

    CHECK_FIELD_RETURN(LogTemp, IconRenderActorClass);

    UClass* TargetActorClass = nullptr;

    if (auto ContextActor = Cast<AActor>(ContextObject))
    {
        TargetActorClass = ContextActor->GetClass();
    }
    else if (auto ContextClass = Cast<UClass>(ContextObject))
    {
        if (ContextClass->IsChildOf(AActor::StaticClass()))
        {
            TargetActorClass = ContextClass;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("UIconWidget::OnContextObjectSet - Provided UClass is not an Actor class."));
            return;
        }
    }

    CHECK_FIELD_RETURN(LogTemp, TargetActorClass);

    FOnIconReady IconReadyDelegate;
    IconReadyDelegate.BindDynamic(this, &UUnitIconWidget::OnIconReady);

    CurrentRequestId = UIconRenderLibrary::RequestIcon(this, IconRenderActorClass, TargetActorClass, IconReadyDelegate);
}

void UUnitIconWidget::OnIconReady(UTexture* Icon, int32 RequestId)
{
    if (CurrentRequestId != RequestId)
        return;

    if (!UnitIcon)
        return;

    CHECK_FIELD_RETURN(LogTemp, Icon);

    auto DynamicMaterial = UnitIcon->GetDynamicMaterial();
    CHECK_FIELD_RETURN(LogTemp, DynamicMaterial);

    DynamicMaterial->SetTextureParameterValue(TEXT("Icon"), Icon);
    DynamicMaterial->SetScalarParameterValue(TEXT("IsLoading"), 0.f);
}

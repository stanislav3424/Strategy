// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitIconWidget.h"
#include "IconRenderLibrary.h"
#include "Components/Image.h"
#include "CheckFieldMacros.h"

void UUnitIconWidget::OnContextObjectSet(UObject* NewContextObject)
{
    Super::OnContextObjectSet(NewContextObject);

    CHECK_FIELD_RETURN(LogTemp, NewContextObject);
    CHECK_FIELD_RETURN(LogTemp, IconRenderActorClass);

    UClass* TargetActorClass = nullptr;

    if (auto ContextActor = Cast<AActor>(NewContextObject))
    {
        TargetActorClass = ContextActor->GetClass();
    }
    else if (auto ContextClass = Cast<UClass>(NewContextObject))
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

    UIconRenderLibrary::RequestIcon(this, IconRenderActorClass, TargetActorClass, IconReadyDelegate);
}

void UUnitIconWidget::OnIconReady(UTexture* Icon)
{
    if (!UnitIcon)
        return;

    CHECK_FIELD_RETURN(LogTemp, Icon);

    auto DynamicMaterial = UnitIcon->GetDynamicMaterial();
    CHECK_FIELD_RETURN(LogTemp, DynamicMaterial);

    DynamicMaterial->SetTextureParameterValue(TEXT("Icon"), Icon);
    DynamicMaterial->SetScalarParameterValue(TEXT("IsLoading"), 0.f);
}

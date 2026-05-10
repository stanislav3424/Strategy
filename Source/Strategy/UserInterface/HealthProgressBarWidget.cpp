// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInterface/HealthProgressBarWidget.h"
#include "Units/UnitComponent/ArmorComponent.h"
#include "CheckFieldMacros.h"

void UHealthProgressBarWidget::NativeConstruct()
{
    Super::NativeConstruct();

    auto ArmorComponent = GetComponent<UArmorComponent>(ContextObject);
    CHECK_FIELD_RETURN(LogTemp, ArmorComponent);

    ArmorComponent->OnHealthChanged.AddUniqueDynamic(this, &UHealthProgressBarWidget::SetPercent);
}

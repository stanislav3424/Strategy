// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntryWidget.h"
#include "BuildEntryWidget.generated.h"

UCLASS(Blueprintable, Abstract)
class STRATEGY_API UBuildEntryWidget : public UEntryWidget
{
    GENERATED_BODY()

protected:
    virtual void OnContextObjectSet(UObject* NewContextObject);
    virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
};

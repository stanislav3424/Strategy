// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntryWidget.h"
#include "CommandEntryWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class STRATEGY_API UCommandEntryWidget : public UEntryWidget
{
	GENERATED_BODY()

protected:
    virtual void OnContextObjectSet(UObject* NewContextObject);
    //virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
};

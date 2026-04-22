// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/ContextWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "EntryWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class STRATEGY_API UEntryWidget : public UContextWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

public:
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};

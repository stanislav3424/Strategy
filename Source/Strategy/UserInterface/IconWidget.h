// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/ContextWidget.h"
#include "IconWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class STRATEGY_API UIconWidget : public UContextWidget
{
	GENERATED_BODY()

protected:
    virtual void OnContextObjectSet(UObject* NewContextObject) override;

    UPROPERTY(meta = (BindWidget))
    class UImage* Icon;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ContextWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class STRATEGY_API UContextWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void ContextObjectSet(UObject* NewContextObject);

protected:
    virtual void OnContextObjectSet(UObject* NewContextObject);
    void ChildContextObjectSet();

    UPROPERTY(BlueprintReadOnly, Category = "ContextObject")
    UObject* ContextObject;
};

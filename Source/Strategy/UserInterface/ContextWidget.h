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
    template <typename TypeComponent> static TypeComponent* GetComponent(UObject* ContextObject)
    {
        auto Component = Cast<TypeComponent>(ContextObject);
        if (Component)
            return Component;
        auto Actor = Cast<AActor>(ContextObject);
        if (!Actor)
            return nullptr;
        Component = Actor->FindComponentByClass<TypeComponent>();
        return Component;
    }

    void SetContext(UObject* NewContextObject);

protected:
    virtual void OnContextObjectSet(UObject* NewContextObject);
    void         ChildContextObjectSet(UObject* NewContextObject);
    void         UpdateAllConstructs();

    UPROPERTY(BlueprintReadOnly, Category = "ContextObject")
    UObject* ContextObject;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContextWidget.h"
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

    UFUNCTION()
    void OnIconReady(UTexture* Icon);

    UPROPERTY(meta = (BindWidget))
    class UImage* UnitIcon;

    UPROPERTY(EditDefaultsOnly, Category = "IconRenderActorClass")
    TSubclassOf<class AIconRenderActor> IconRenderActorClass;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UnitEntryWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class STRATEGY_API UUnitEntryWidget : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

public:
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
    UFUNCTION()
    void OnIconReady(UTexture* Icon);

    UPROPERTY(meta = (BindWidget))
    class UImage* UnitIcon;

    UPROPERTY(EditDefaultsOnly, Category = "IconRenderActorClass")
    TSubclassOf<class AIconRenderActor> IconRenderActorClass;
};

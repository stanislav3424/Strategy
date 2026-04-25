// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContextWidget.h"
#include "UnitIconWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class STRATEGY_API UUnitIconWidget : public UContextWidget
{
    GENERATED_BODY()

protected:
    virtual void NativePreConstruct() override;

    UFUNCTION()
    void OnIconReady(UTexture* Icon, int32 RequestId);

    UPROPERTY(meta = (BindWidget))
    class UImage* UnitIcon;

    UPROPERTY(EditDefaultsOnly, Category = "IconRenderActorClass")
    TSubclassOf<class AIconRenderActor> IconRenderActorClass;
    
    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    int32 CurrentRequestId = INDEX_NONE;
};

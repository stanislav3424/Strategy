// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/ContextWidget.h"
#include "ProgressBarWidget.generated.h"

/**
 * Base class for progress bar widgets.
 */
UCLASS(NotBlueprintable, Abstract)
class STRATEGY_API UProgressBarWidget : public UContextWidget
{
    GENERATED_BODY()

protected:
    UFUNCTION(BlueprintCallable)
    void SetPercent(float CurrentValue, float MaxValue);
    
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* ProgressBar;


};

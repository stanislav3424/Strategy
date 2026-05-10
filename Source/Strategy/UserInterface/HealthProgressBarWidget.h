// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/ProgressBarWidget.h"
#include "HealthProgressBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class STRATEGY_API UHealthProgressBarWidget : public UProgressBarWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;
};

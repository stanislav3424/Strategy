// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInterface/ProgressBarWidget.h"
#include "Components/ProgressBar.h"

void UProgressBarWidget::SetPercent(float CurrentValue, float MaxValue)
{
    if (!ProgressBar)
        return;
    
    ProgressBar->SetPercent(CurrentValue / MaxValue);
}

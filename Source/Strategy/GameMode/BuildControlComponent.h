// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseControlComponent.h"
#include "BuildControlComponent.generated.h"


UCLASS(ClassGroup = (ControlComponent))
class STRATEGY_API UBuildControlComponent : public UBaseControlComponent
{
	GENERATED_BODY()

protected:
    virtual void OnSetupInputComponent(UEnhancedInputComponent* InputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* BuildAction;
};

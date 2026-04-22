// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseControlComponent.generated.h"

UCLASS(ClassGroup = (ControlComponent))
class STRATEGY_API UBaseControlComponent : public UActorComponent
{
    GENERATED_BODY()

    friend class AGamePlayerController;

protected:
    virtual void OnActivateInput() {};
    virtual void OnDeactivateInput() {};
    virtual void OnSetupInputComponent(UEnhancedInputComponent* InputComponent) {};
    void         ActivateInput();
    void         DeactivateInput();
    void         SetupInputComponent(UEnhancedInputComponent* InputComponent);

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputMappingContext* InputMappingContext;

    UPROPERTY(BlueprintReadOnly, Category = "Debug")
    class APlayerController* PlayerController;

private:
    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    class UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem;
};

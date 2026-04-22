// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FSwitchControlComponent, class UBaseControlComponent*, CurrentControlComponent);

/**
 *
 */
UCLASS(Blueprintable, Abstract)
class STRATEGY_API AGamePlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AGamePlayerController();

    virtual void Tick(float DeltaSeconds) override;
    void         SetSelectionControl();
    void         SetBuildControl();
    void         SwitchControl();

    static FVector GetMouseWorldLocation(APlayerController* PlayerController);

    UPROPERTY(BlueprintAssignable)
    FSwitchControlComponent OnSwitchControlComponent;

    void BroadcastSwitchControlComponent();

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    void OnSwitchControl(struct FInputActionValue const& InputAction);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USelectionControlComponent* SelectionControlComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UBuildControlComponent* BuildControlComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputMappingContext* DefaultInputMappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* SwitchControlAction;

private:
    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    class UBaseControlComponent* CurrentControlComponent;
};

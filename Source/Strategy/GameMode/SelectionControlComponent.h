// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/BaseControlComponent.h"
#include "SelectionControlComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUpdateSelectedActors, TArray<AActor*>, SelectedActors, TArray<AActor*>,
    ActorsToDeselect, TArray<AActor*>, ActorsToSelect);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUpdateAvailableCommands, TArray<TSubclassOf<class UCommandObject>>,
    AvailableCommands, TArray<TSubclassOf<class UCommandObject>>, AvailableCommandsToRemove,
    TArray<TSubclassOf<class UCommandObject>>, AvailableCommandsToAdd, TSubclassOf<class UCommandObject>,
    CurrentCommand);


UCLASS(ClassGroup = (ControlComponent))
class STRATEGY_API USelectionControlComponent : public UBaseControlComponent
{
    GENERATED_BODY()

public:
    USelectionControlComponent();

    bool         IsSelection() const { return bIsSelection; }
    FVector      GetStartSelectionLocation() const { return StartSelectionLocation; }
    FVector      GetEndSelectionLocation() const { return EndSelectionLocation; }
    void         UpdateSelectionActors(TArray<AActor*> const& NewSelectedActors);
    AActor*      GetActorUnderMouseCursor() const;
    virtual void TickComponent(
        float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void SelectionStarted();
    void SelectionCompleted();
    void SetCurrentCommand(TSubclassOf<class UCommandObject> NewCommand);

    UPROPERTY(BlueprintAssignable)
    FOnUpdateSelectedActors OnUpdateSelectedActors;

    UPROPERTY(BlueprintAssignable)
    FOnUpdateAvailableCommands OnUpdateAvailableCommands;

protected:
    virtual void OnSetupInputComponent(UEnhancedInputComponent* InputComponent) override;
    virtual void OnDeactivateInput() override;

    void OnSelectionStarted(struct FInputActionValue const& InputAction);
    void OnSelectionCompleted(struct FInputActionValue const& InputAction);
    void OnCommand(struct FInputActionValue const& InputAction);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* SelectionAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* CommandAction;

private:
    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    bool bIsSelection = false;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    bool bIsDetectSelection = false;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    FVector StartSelectionLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    FVector EndSelectionLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TSet<AActor*> SelectedActors;

    UPROPERTY(EditDefaultsOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    float DistanceThreshold = 25.f;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TSet<TSubclassOf<class UCommandObject>> AvailableCommands;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UCommandObject> CurrentCommand;

};

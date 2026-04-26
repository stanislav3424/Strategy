// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseControlComponent.h"
#include "BuildControlComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUpdateAvailableBuild, TArray<TSubclassOf<AActor>>, AvailableBuilds, TArray<TSubclassOf<AActor>>, AvailableBuildsToRemove, TArray<TSubclassOf<AActor>>, AvailableBuildsToAdd, TSubclassOf<AActor>, CurrentBuild);

UCLASS(ClassGroup = (ControlComponent))
class STRATEGY_API UBuildControlComponent : public UBaseControlComponent
{
	GENERATED_BODY()

public:
    virtual void TickComponent(
        float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void SwitchAvailableBuilds(bool bNext);
    void SelectAvailableBuild(int32 Index);
    void SelectAvailableBuild(TSubclassOf<AActor> BuildClass);
    TArray<TSubclassOf<AActor>> GetAvailableBuilds() const { return AvailableBuilds; }

    UPROPERTY(BlueprintAssignable)
    FOnUpdateAvailableBuild OnUpdateAvailableBuild;
protected:
    virtual void BeginPlay() override;
    virtual void OnSetupInputComponent(UEnhancedInputComponent* InputComponent) override;
    virtual void OnDeactivateInput() override;

    void OnBuild(struct FInputActionValue const& InputAction);
    void OnRotate(struct FInputActionValue const& InputAction);
    void OnSwitchAvailableBuilds(struct FInputActionValue const& InputAction);

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* BuildAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* RotateAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* SwitchAvailableBuildsAction;

    UPROPERTY(EditDefaultsOnly, Category = "GhostMaterial")
    class UMaterialInterface* GhostTrueActorMaterial;

    UPROPERTY(EditDefaultsOnly, Category = "GhostMaterial")
    class UMaterialInterface* GhostFalseActorMaterial;

    // Temporary
    UPROPERTY(EditDefaultsOnly, Category = "AvailableBuilds")
    TArray<TSubclassOf<AActor>> AvailableBuilds;

private:
    void UpdateGhostActor();
    void UpdateGhostActorOverlap();
    void UpdateGhostActorMaterial();
    void SpawnGhostActor();
    void DestroyGhostActor();

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    bool bIsGhost = false;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    bool bIsGhostOverlap = false;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    AActor* GhostActor;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AActor> GhostActorClass;
};

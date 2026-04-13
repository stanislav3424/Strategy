// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SelectionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectionChanged, bool, bIsSelected);

UCLASS(ClassGroup = (UnitComponent))
class STRATEGY_API USelectionComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    USelectionComponent();
    void SetSelected(bool bSelected);
    bool IsSelected() const { return bIsSelected; }

    UFUNCTION(BlueprintCallable)
    static USelectionComponent* GetSelectionComponent(AActor* Actor);

    UFUNCTION(BlueprintCallable)
    static bool IsSelected(AActor* Actor);

    UFUNCTION(BlueprintCallable)
    static void SetSelected(AActor* Actor, bool bSelected);

    UPROPERTY(BlueprintAssignable)
    FOnSelectionChanged OnSelectionChanged;

protected:
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = "Unit Factory")
    class UStaticMeshComponent* SelectionMesh;

private:
    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    bool bIsSelected = false;
};

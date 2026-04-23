// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntryWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UnitEntryWidget.generated.h"

UCLASS(NotBlueprintable)
class UUnitEntryObject : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, Category = "UnitsInfo")
    TSubclassOf<AActor> UnitClass;

    UPROPERTY(BlueprintReadOnly, Category = "UnitsInfo")
    int32 NumUnits = 0;

    UPROPERTY(BlueprintReadOnly, Category = "UnitsInfo")
    TArray<AActor*> Units;
};

/**
 *
 */
UCLASS(Blueprintable, Abstract) class STRATEGY_API UUnitEntryWidget : public UEntryWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
    virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

    UFUNCTION(BlueprintCallable, Category = "UnitsInfo")
    TSubclassOf<AActor> GetUnitClass() const;

    UFUNCTION(BlueprintCallable, Category = "UnitsInfo")
    int32 GetNumUnits() const;

    UFUNCTION(BlueprintCallable, Category = "UnitsInfo")
    TArray<AActor*> GetUnits() const;
};

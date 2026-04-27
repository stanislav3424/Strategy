// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "HUD_Widget.generated.h"

UCLASS(NotBlueprintable)
class USelectionDragDropOperation : public UDragDropOperation
{
    GENERATED_BODY()
};

/**
 *
 */
UCLASS(Blueprintable, Abstract)
class STRATEGY_API UHUDWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void  NativeConstruct() override;
    virtual int32 NativePaint(FPaintArgs const& Args, FGeometry const& AllottedGeometry,
        FSlateRect const& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
        FWidgetStyle const& InWidgetStyle, bool bParentEnabled) const override;

    void UpdateListViewBuilds(TArray<TSubclassOf<AActor>> AvailableBuilds);

    // UFUNCTION()
    // void OnSwitchControlComponent(class UBaseControlComponent* CurrentControlComponent);

    UFUNCTION()
    void OnUpdateSelectedActors(TArray<AActor*> SelectedActors);

    UFUNCTION()
    void OnUpdateAvailableCommands(
        TArray<TSubclassOf<class UCommandTask>> AvailableCommands, TSubclassOf<class UCommandTask> CurrentCommand);

    void SetIndexWidgetSwitchers(int32 Index);

    UFUNCTION()
    void OnButtonSelectionUnitsClicked();

    UFUNCTION()
    void OnButtonProductionClicked();

    UFUNCTION()
    void OnButtonBuildingClicked();

    UPROPERTY(meta = (BindWidget))
    class UListView* ListViewUnits;

    UPROPERTY(meta = (BindWidget))
    class UListView* ListViewBuilds;

    UPROPERTY(meta = (BindWidget))
    class UWidgetSwitcher* WidgetSwitcherButtons;

    UPROPERTY(meta = (BindWidget))
    class UWidgetSwitcher* WidgetSwitcherLists;

    UPROPERTY(meta = (BindWidget))
    class UButton* ButtonSelectionUnits;

    UPROPERTY(meta = (BindWidget))
    class UButton* ButtonBuilding;

    UPROPERTY(meta = (BindWidget))
    class UButton* ButtonProduction;

    UPROPERTY(meta = (BindWidget))
    class UTileView* TileViewCommands;

    UPROPERTY(meta = (BindWidget))
    class UTileView* TileViewBuilds;

    UPROPERTY(EditDefaultsOnly, Category = "Selection")
    class USlateBrushAsset* SlateBrushAssetBox;

    UPROPERTY(EditDefaultsOnly, Category = "Selection")
    class USlateBrushAsset* SlateBrushAssetBorder;

    UPROPERTY(EditDefaultsOnly, Category = "Selection")
    FLinearColor SelectionColorBox = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, Category = "Selection")
    FLinearColor SelectionColorBorder = FLinearColor::Black;

private:
    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    class AGamePlayerController* PlayerController;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    class USelectionControlComponent* SelectionControlComponent;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    class UBuildControlComponent* BuildControlComponent;
};

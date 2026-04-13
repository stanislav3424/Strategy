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

private:
    UPROPERTY(EditDefaultsOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    class USlateBrushAsset* SlateBrushAssetBox;

    UPROPERTY(EditDefaultsOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    class USlateBrushAsset* SlateBrushAssetBorder;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    class AGamePlayerController* PlayerController;

    UPROPERTY(EditDefaultsOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    FLinearColor SelectionColorBox = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    FLinearColor SelectionColorBorder = FLinearColor::Black;
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD_Widget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "GamePlayerController.h"

void UHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    auto World = GetWorld();
    if (!World)
        return;

    PlayerController = Cast<AGamePlayerController>(World->GetFirstPlayerController());
}

int32 UHUDWidget::NativePaint(FPaintArgs const& Args, FGeometry const& AllottedGeometry,
    FSlateRect const& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
    FWidgetStyle const& InWidgetStyle, bool bParentEnabled) const
{
    int32 MaxLayer = Super::NativePaint(
        Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

    if (PlayerController && PlayerController->IsSelection())
    {
        auto World = GetWorld();
        if (!World)
            return MaxLayer;

        FVector2D ScreenStart;
        PlayerController->ProjectWorldLocationToScreen(PlayerController->GetStartSelectionLocation(), ScreenStart);
        FVector2D ScreenEnd;
        PlayerController->ProjectWorldLocationToScreen(PlayerController->GetEndSelectionLocation(), ScreenEnd);

        FVector2D LocalStart;
        USlateBlueprintLibrary::ScreenToWidgetLocal(this, AllottedGeometry, ScreenStart, LocalStart, true);
        FVector2D LocalEnd;
        USlateBlueprintLibrary::ScreenToWidgetLocal(this, AllottedGeometry, ScreenEnd, LocalEnd, true);

        FVector2D LocalPosition =
            FVector2D(FMath::Min(LocalStart.X, LocalEnd.X), FMath::Min(LocalStart.Y, LocalEnd.Y));
        FVector2D LocalSize =
            FVector2D(FMath::Abs(LocalEnd.X - LocalStart.X), FMath::Abs(LocalEnd.Y - LocalStart.Y));

        FPaintContext Context(
            AllottedGeometry, MyCullingRect, OutDrawElements, MaxLayer, InWidgetStyle, bParentEnabled);
        UWidgetBlueprintLibrary::DrawBox(Context, LocalPosition, LocalSize, SlateBrushAssetBox, SelectionColorBox);
        UWidgetBlueprintLibrary::DrawBox(Context, LocalPosition, LocalSize, SlateBrushAssetBorder, SelectionColorBorder);

        return FMath::Max(MaxLayer, LayerId + 1);
    }

    return MaxLayer;
}
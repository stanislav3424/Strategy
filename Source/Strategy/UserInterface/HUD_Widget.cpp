// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD_Widget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "GamePlayerController.h"
#include "SelectionControlComponent.h"
#include "BuildControlComponent.h"
#include "CheckFieldMacros.h"
#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"

void UHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    auto World = GetWorld();
    if (!World)
        return;

    PlayerController = Cast<AGamePlayerController>(World->GetFirstPlayerController());
    CHECK_FIELD_RETURN(LogTemp, PlayerController);

    SelectionControlComponent = PlayerController->FindComponentByClass<USelectionControlComponent>();
    CHECK_FIELD_RETURN(LogTemp, SelectionControlComponent);

    BuildControlComponent = PlayerController->FindComponentByClass<UBuildControlComponent>();
    CHECK_FIELD_RETURN(LogTemp, BuildControlComponent);
    UpdateListViewBuilds(BuildControlComponent->GetAvailableBuilds());

    PlayerController->OnSwitchControlComponent.AddUniqueDynamic(this, &UHUDWidget::OnSwitchControlComponent);
    PlayerController->BroadcastSwitchControlComponent();

    SelectionControlComponent->OnUpdateSelectedActors.AddUniqueDynamic(this, &UHUDWidget::OnUpdateSelectedActors);
}

int32 UHUDWidget::NativePaint(FPaintArgs const& Args, FGeometry const& AllottedGeometry,
    FSlateRect const& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
    FWidgetStyle const& InWidgetStyle, bool bParentEnabled) const
{
    int32 MaxLayer = Super::NativePaint(
        Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

    if (PlayerController && SelectionControlComponent && SelectionControlComponent->IsSelection())
    {
        auto World = GetWorld();
        if (!World)
            return MaxLayer;

        FVector2D ScreenStart;
        PlayerController->ProjectWorldLocationToScreen(
            SelectionControlComponent->GetStartSelectionLocation(), ScreenStart);
        FVector2D ScreenEnd;
        PlayerController->ProjectWorldLocationToScreen(SelectionControlComponent->GetEndSelectionLocation(), ScreenEnd);

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

void UHUDWidget::UpdateListViewBuilds(TArray<TSubclassOf<AActor>> AvailableBuilds)
{
    if (!ListViewBuilds)
        return;

    ListViewBuilds->ClearListItems();
    for (auto Actor : AvailableBuilds)
    {
        ListViewBuilds->AddItem(Actor);
    }
}

void UHUDWidget::OnSwitchControlComponent(UBaseControlComponent* CurrentControlComponent)
{
    if (!WidgetSwitcher)
        return;

    // Temporary
    if (CurrentControlComponent == SelectionControlComponent)
        WidgetSwitcher->SetActiveWidgetIndex(0); // Units == 0
    else
        WidgetSwitcher->SetActiveWidgetIndex(1); // Builds == 1
}

void UHUDWidget::OnUpdateSelectedActors(TArray<AActor*> SelectedActors, TArray<AActor*> ActorsToDeselect,
    TArray<AActor*> ActorsToSelect)
{
    if (!ListViewUnits)
        return;

    // Temporary
    ListViewUnits->ClearListItems();
    for (auto Actor : SelectedActors)
    {
        ListViewUnits->AddItem(Actor);
    }
}   
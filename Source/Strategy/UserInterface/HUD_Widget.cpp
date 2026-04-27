// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD_Widget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "GamePlayerController.h"
#include "SelectionControlComponent.h"
#include "BuildControlComponent.h"
#include "CheckFieldMacros.h"
#include "Components/ListView.h"
#include "Components/TileView.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "CommandEntryWidget.h"
#include "UserInterface/UnitEntryWidget.h"

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

    //PlayerController->OnSwitchControlComponent.AddUniqueDynamic(this, &UHUDWidget::OnSwitchControlComponent);
    //PlayerController->BroadcastSwitchControlComponent();

    SelectionControlComponent->OnUpdateSelectedActors.AddUniqueDynamic(this, &UHUDWidget::OnUpdateSelectedActors);
    SelectionControlComponent->OnUpdateAvailableCommandTasks.AddUniqueDynamic(
        this, &UHUDWidget::OnUpdateAvailableCommands);

    if (!ButtonSelectionUnits)
        return;
    ButtonSelectionUnits->OnClicked.AddUniqueDynamic(this, &UHUDWidget::OnButtonSelectionUnitsClicked);

    if (!ButtonProduction)
        return;
    ButtonProduction->OnClicked.AddUniqueDynamic(this, &UHUDWidget::OnButtonProductionClicked);

    if (!ButtonBuilding)
        return;
    ButtonBuilding->OnClicked.AddUniqueDynamic(this, &UHUDWidget::OnButtonBuildingClicked);
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

//void UHUDWidget::OnSwitchControlComponent(UBaseControlComponent* CurrentControlComponent)
//{
//    if (!WidgetSwitcherButtons)
//        return;
//
//    // Temporary
//    if (CurrentControlComponent == SelectionControlComponent)
//        WidgetSwitcherButtons->SetActiveWidgetIndex(0); // Units == 0
//    else
//        WidgetSwitcherButtons->SetActiveWidgetIndex(1); // Builds == 1
//}

void UHUDWidget::OnUpdateSelectedActors(TArray<AActor*> SelectedActors)
{
    if (!ListViewUnits)
        return;

    TMap<TSubclassOf<AActor>, TPair<int32, TArray<AActor*>>> UnitClassCounts;
    for (auto Actor : SelectedActors)
        if (Actor)
        {
            auto& UnitClassCount = UnitClassCounts.FindOrAdd(Actor->GetClass());
            UnitClassCount.Key++;
            UnitClassCount.Value.Add(Actor);
        }

    ListViewUnits->ClearListItems();
    for (auto const& Elem : UnitClassCounts)
    {
        auto EntryObject = NewObject<UUnitEntryObject>(this);
        if (!EntryObject)
            continue;
        EntryObject->UnitClass = Elem.Key;
        EntryObject->NumUnits  = Elem.Value.Key;
        EntryObject->Units     = Elem.Value.Value;
        ListViewUnits->AddItem(EntryObject);
    }
}

void UHUDWidget::OnUpdateAvailableCommands(
    TArray<TSubclassOf<class UCommandTask>> AvailableCommands, TSubclassOf<class UCommandTask> CurrentCommand)
{
    if (!TileViewCommands)
        return;
    TileViewCommands->ClearListItems();
    for (auto CommandClass : AvailableCommands)
    {
        TileViewCommands->AddItem(CommandClass);
        if (CommandClass == CurrentCommand)
        {
            TileViewCommands->SetSelectedItem(CommandClass);
        }
    }
}

void UHUDWidget::SetIndexWidgetSwitchers(int32 Index)
{
    if (!WidgetSwitcherButtons || !WidgetSwitcherLists)
        return;

    WidgetSwitcherButtons->SetActiveWidgetIndex(Index);
    WidgetSwitcherLists->SetActiveWidgetIndex(Index);
}

void UHUDWidget::OnButtonSelectionUnitsClicked()
{
    SetIndexWidgetSwitchers(0);
}

void UHUDWidget::OnButtonProductionClicked()
{
    SetIndexWidgetSwitchers(1);
}

void UHUDWidget::OnButtonBuildingClicked()
{
    SetIndexWidgetSwitchers(2);
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHUD.h"
#include "HUD_Widget.h"
#include "CheckFieldMacros.h"
#include "GamePlayerController.h"
#include "SelectionControlComponent.h"

void AGameHUD::BeginPlay()
{
    Super::BeginPlay();

    auto World = GetWorld();
    if (!World)
        return;

    PlayerController = Cast<AGamePlayerController>(World->GetFirstPlayerController());
    CHECK_FIELD_RETURN(LogTemp, PlayerController);

    SelectionControlComponent = PlayerController->FindComponentByClass<USelectionControlComponent>();
    CHECK_FIELD_RETURN(LogTemp, SelectionControlComponent);

    CHECK_FIELD_RETURN(LogTemp, HUDWidgetClass);
    HUDWidget = CreateWidget<UHUDWidget>(World, HUDWidgetClass);
    CHECK_FIELD_RETURN(LogTemp, HUDWidget);
    HUDWidget->AddToViewport(0);
}

void AGameHUD::DrawHUD()
{
    Super::DrawHUD();

    if (!PlayerController)
        return;

    if (!SelectionControlComponent || !SelectionControlComponent->IsSelection())
        return;

    FVector2D ScreenStart;
    FVector   StartLocation = SelectionControlComponent->GetStartSelectionLocation();
    PlayerController->ProjectWorldLocationToScreen(StartLocation, ScreenStart);
    FVector2D ScreenEnd;
    FVector   EndLocation = SelectionControlComponent->GetEndSelectionLocation();
    PlayerController->ProjectWorldLocationToScreen(EndLocation, ScreenEnd);

    TArray<AActor*> SelectedActors;
    GetActorsInSelectionRectangle(ScreenStart, ScreenEnd, SelectedActors, false, false);

    for (auto Iterator = SelectedActors.CreateIterator(); Iterator; ++Iterator)
    {
        auto Actor = *Iterator;
        if (!Actor)
        {
            Iterator.RemoveCurrent();
            continue;
        }

        FVector2D Screen;
        PlayerController->ProjectWorldLocationToScreen(Actor->GetActorLocation(), Screen);

        if (!IsPointInsideRectangle(Screen, ScreenStart, ScreenEnd))
        {
            Iterator.RemoveCurrent();
        }
    }

    SelectionControlComponent->UpdateSelectionActors(SelectedActors);

    // Debug code to draw selection rectangle using HUD's Canvas
    // DrawRect(FLinearColor::Green, ScreenStart.X, ScreenStart.Y, ScreenEnd.X - ScreenStart.X, ScreenEnd.Y - ScreenStart.Y);
}

bool AGameHUD::IsPointInsideRectangle(const FVector2D& Point, const FVector2D& RectStart, const FVector2D& RectEnd)
{
    float MinX = FMath::Min(RectStart.X, RectEnd.X);
    float MaxX = FMath::Max(RectStart.X, RectEnd.X);
    float MinY = FMath::Min(RectStart.Y, RectEnd.Y);
    float MaxY = FMath::Max(RectStart.Y, RectEnd.Y);

    return (Point.X >= MinX && Point.X <= MaxX && Point.Y >= MinY && Point.Y <= MaxY);
}
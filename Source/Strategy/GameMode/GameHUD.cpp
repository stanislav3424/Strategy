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
    CHECK_FIELD(LogTemp, PlayerController);

    SelectionControlComponent = PlayerController->FindComponentByClass<USelectionControlComponent>();
    CHECK_FIELD(LogTemp, SelectionControlComponent);

    HUDWidget = CreateWidget<UHUDWidget>(World, HUDWidgetClass);
    CHECK_FIELD(LogTemp, HUDWidget);

    HUDWidget->AddToViewport();
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
    GetActorsInSelectionRectangle(ScreenStart, ScreenEnd, SelectedActors, true, false);

    SelectionControlComponent->UpdateSelectionActors(SelectedActors);

    // Debug code to draw selection rectangle using HUD's Canvas
    // DrawRect(FLinearColor::Green, ScreenStart.X, ScreenStart.Y, ScreenEnd.X - ScreenStart.X, ScreenEnd.Y - ScreenStart.Y);
}

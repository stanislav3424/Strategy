// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHUD.h"
#include "HUD_Widget.h"
#include "CheckFieldMacros.h"
#include "GamePlayerController.h"

void AGameHUD::BeginPlay()
{
    Super::BeginPlay();

    auto World = GetWorld();
    if (!World)
        return;

    PlayerController = Cast<AGamePlayerController>(World->GetFirstPlayerController());
    CHECK_FIELD_RETURN(LogTemp, HUDWidgetClass);

    HUDWidget = CreateWidget<UHUDWidget>(World, HUDWidgetClass);
    if (!HUDWidget)
        return;

    HUDWidget->AddToViewport();
}

void AGameHUD::DrawHUD()
{
    Super::DrawHUD();

    if (!PlayerController)
        return;

    if (!PlayerController->IsSelection())
        return;

    FVector2D ScreenStart;
    FVector   StartLocation = PlayerController->GetStartSelectionLocation();
    PlayerController->ProjectWorldLocationToScreen(StartLocation, ScreenStart);
    FVector2D ScreenEnd;
    FVector   EndLocation = PlayerController->GetEndSelectionLocation();
    PlayerController->ProjectWorldLocationToScreen(EndLocation, ScreenEnd);

    TArray<AActor*> SelectedActors;
    GetActorsInSelectionRectangle(ScreenStart, ScreenEnd, SelectedActors, true, false);

    PlayerController->UpdateSelectionActors(SelectedActors);

    // Debug code to draw selection rectangle using HUD's Canvas
    // DrawRect(FLinearColor::Green, ScreenStart.X, ScreenStart.Y, ScreenEnd.X - ScreenStart.X, ScreenEnd.Y - ScreenStart.Y);
}

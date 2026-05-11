// Fill out your copyright notice in the Description page of Project Settings.

#include "SelectionComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CheckFieldMacros.h"
#include "CharacterUnit.h"
#include "PawnUnit.h"

USelectionComponent::USelectionComponent()
{
}

void USelectionComponent::SetSelected(bool bSelected)
{
    if (bIsSelected == bSelected)
        return;

    bIsSelected = bSelected;
    if (SelectionMesh)
        SelectionMesh->SetVisibility(bIsSelected);
}

USelectionComponent* USelectionComponent::GetSelectionComponent(AActor* Actor)
{
    CHECK_FIELD_RETURN_VAL(LogTemp, Actor, nullptr);

    auto Component = Actor->FindComponentByClass<USelectionComponent>();

    CHECK_FIELD_RETURN_VAL(LogTemp, Component, nullptr);

    return Component;
}

bool USelectionComponent::IsSelected(AActor* Actor)
{
    if (!Actor)
        return false;

    auto SelectionComponent = Actor->FindComponentByClass<USelectionComponent>();
    if (!SelectionComponent)
        return false;

    return SelectionComponent->IsSelected();
}

void USelectionComponent::SetSelected(AActor* Actor, bool bSelected)
{
    if (!Actor)
        return;

    auto SelectionComponent = Actor->FindComponentByClass<USelectionComponent>();
    if (!SelectionComponent)
        return;

    SelectionComponent->SetSelected(bSelected);
}

void USelectionComponent::BeginPlay()
{
    Super::BeginPlay();

    if (auto CharacterUnit = Cast<ACharacterUnit>(GetOwner()))
    {

        SelectionMesh = CharacterUnit->GetSelectionMesh();
        CHECK_FIELD_RETURN(LogTemp, SelectionMesh);

        SelectionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        SelectionMesh->bHiddenInSceneCapture = true;

        SetSelected(false);
    }

    if (auto PawnUnit = Cast<APawnUnit>(GetOwner()))
    {

        SelectionMesh = PawnUnit->GetSelectionMesh();
        CHECK_FIELD_RETURN(LogTemp, SelectionMesh);

        SelectionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        SelectionMesh->bHiddenInSceneCapture = true;

        SetSelected(false);
    }
}
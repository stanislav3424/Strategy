// Fill out your copyright notice in the Description page of Project Settings.

#include "SelectionComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CheckFieldMacros.h"

USelectionComponent::USelectionComponent()
{
    SelectionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectionMesh"));
    SelectionMesh->SetupAttachment(this);
    SelectionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void USelectionComponent::SetSelected(bool bSelected)
{
    if (bIsSelected == bSelected)
        return;

    bIsSelected = bSelected;
    SelectionMesh->SetVisibility(bIsSelected);
}

USelectionComponent* USelectionComponent::GetSelectionComponent(AActor* Actor)
{
    if (!Actor)
        return nullptr;

    if (auto Component = Actor->FindComponentByClass<USelectionComponent>())
        return Component;

    UE_LOG(LogTemp, Error, TEXT("USelectionComponent::GetSelectionComponent - Actor %s does not have a SelectionComponent!"),
        *Actor->GetName());

    return nullptr;
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

    SetSelected(false);
}

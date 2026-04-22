// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildControlComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CheckFieldMacros.h"
#include "GamePlayerController.h"
#include "Materials/MaterialInterface.h"

void UBuildControlComponent::TickComponent(
    float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UpdateGhostActor();
}

void UBuildControlComponent::SwitchAvailableBuilds(bool bNext)
{
}

void UBuildControlComponent::SelectAvailableBuild(int32 Index)
{
    if (AvailableBuilds.IsValidIndex(Index))
        SelectAvailableBuild(AvailableBuilds[Index]);
    else
        return;

    UE_LOG(
        LogTemp, Error, TEXT("UBuildControlComponent::SelectAvailableBuild(int32 Index) - Not valid index: %d"), Index);

    if (AvailableBuilds.IsValidIndex(0))
        SelectAvailableBuild(AvailableBuilds[0]);
}

void UBuildControlComponent::SelectAvailableBuild(TSubclassOf<AActor> BuildClass)
{
    if (!AvailableBuilds.Contains(BuildClass))
    {
        UE_LOG(LogTemp, Error,
            TEXT("UBuildControlComponent::SelectAvailableBuild(TSubclassOf<AActor> BuildClass) - Not valid build "
                 "class: %s"),
            *GetNameSafe(BuildClass));
        return;
    }

    GhostActorClass = BuildClass;
    SpawnGhostActor();
    UpdateGhostActor();
}

void UBuildControlComponent::BeginPlay()
{
    Super::BeginPlay();

    CHECK_FIELD(LogTemp, GhostTrueActorMaterial);
    CHECK_FIELD(LogTemp, GhostFalseActorMaterial);

    if (AvailableBuilds.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("UBuildControlComponent::BeginPlay - No available builds."));
        return;
    }

    for (auto AvailableBuild : AvailableBuilds)
    {
        CHECK_FIELD(LogTemp, AvailableBuild);
    }
}

void UBuildControlComponent::OnSetupInputComponent(UEnhancedInputComponent* InputComponent)
{
    Super::OnSetupInputComponent(InputComponent);

    if (!InputComponent)
        return;

    CHECK_FIELD_RETURN(LogTemp, BuildAction);
    InputComponent->BindAction(BuildAction, ETriggerEvent::Started, this, &UBuildControlComponent::OnBuild);
    CHECK_FIELD_RETURN(LogTemp, RotateAction);
    InputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &UBuildControlComponent::OnRotate);

}

void UBuildControlComponent::OnDeactivateInput()
{
    Super::OnDeactivateInput();

    bIsGhost = false;
    DestroyGhostActor();
}

void UBuildControlComponent::OnBuild(FInputActionValue const& InputAction)
{
    if (bIsGhostOverlap)
        return;
    if (!GhostActor)
        return;

    auto World = GetWorld();
    if (!World)
        return;
    FActorSpawnParameters ActorSpawnParameters;
    ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    World->SpawnActor<AActor>(
        GhostActorClass, GhostActor->GetActorLocation(), GhostActor->GetActorRotation(), ActorSpawnParameters);
}

void UBuildControlComponent::OnRotate(FInputActionValue const& InputAction)
{
    const float RotateValue = InputAction.Get<float>();
    if (!GhostActor)
        return;

    GhostActor->AddActorWorldRotation(FRotator(0.f, RotateValue, 0.f));
}

void UBuildControlComponent::OnSwitchAvailableBuilds(FInputActionValue const& InputAction)
{
    const bool bIsNext = InputAction.Get<bool>();
    SwitchAvailableBuilds(bIsNext);
}

void UBuildControlComponent::UpdateGhostActor()
{
    if (!bIsGhost)
        return;
    if (!PlayerController)
        return;
    if (!GhostActor)
        return;

    const FVector MouseWorldLocation = AGamePlayerController::GetMouseWorldLocation(PlayerController);
    GhostActor->SetActorLocation(MouseWorldLocation);
    UpdateGhostActorOverlap();
    UpdateGhostActorMaterial();
}

void UBuildControlComponent::UpdateGhostActorOverlap()
{
    if (!GhostActor)
        return;
    
    //bIsGhostOverlap = ;
}

void UBuildControlComponent::UpdateGhostActorMaterial()
{
    if (!GhostActor)
        return;
    TArray<UPrimitiveComponent*> PrimitiveComponents;
    GhostActor->GetComponents<UPrimitiveComponent>(PrimitiveComponents, true);
    for (auto PrimitiveComponent : PrimitiveComponents)
    {
        if (!PrimitiveComponent)
            continue;
        const int32 MaterialCount = PrimitiveComponent->GetNumMaterials();
        for (int32 MaterialIndex = 0; MaterialIndex < MaterialCount; ++MaterialIndex)
        {
            PrimitiveComponent->SetMaterial(
                MaterialIndex, bIsGhostOverlap ? GhostFalseActorMaterial : GhostTrueActorMaterial);
        }
    }
}

void UBuildControlComponent::SpawnGhostActor()
{
    if (GhostActor)
        DestroyGhostActor();

    auto World = GetWorld();
    if (!World)
        return;
    const FVector         MouseWorldLocation = AGamePlayerController::GetMouseWorldLocation(PlayerController);
    FActorSpawnParameters ActorSpawnParameters;
    ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    if (GhostActorClass)
        GhostActor =
            World->SpawnActor<AActor>(GhostActorClass, MouseWorldLocation, FRotator::ZeroRotator, ActorSpawnParameters);

    UpdateGhostActorOverlap();
    UpdateGhostActorMaterial();
}

void UBuildControlComponent::DestroyGhostActor()
{
    if (GhostActor)
    {
        GhostActor->Destroy();
        GhostActor = nullptr;
    }
}

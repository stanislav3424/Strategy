// Fill out your copyright notice in the Description page of Project Settings.

#include "IconRenderActor.h"
#include "IconRenderSubsystem.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/TextureRenderTarget2D.h"

AIconRenderActor::AIconRenderActor()
{
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);

    SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2D"));
    SceneCaptureComponent2D->SetupAttachment(SpringArmComponent);
    SceneCaptureComponent2D->ProjectionType                     = ECameraProjectionMode::Orthographic;
    SceneCaptureComponent2D->PrimitiveRenderMode                = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
    SceneCaptureComponent2D->bCaptureEveryFrame                 = false;
    SceneCaptureComponent2D->bCaptureOnMovement                 = false;
    SceneCaptureComponent2D->ViewLightingChannels.bViewChannel0 = false;
    SceneCaptureComponent2D->ViewLightingChannels.bViewChannel1 = true;
    SceneCaptureComponent2D->ViewLightingChannels.bViewChannel2 = false;
    SceneCaptureComponent2D->ViewLightingChannels.bViewChannel3 = false;
    SceneCaptureComponent2D->ViewLightingChannels.bViewChannel4 = false;
}

bool AIconRenderActor::ExecuteRender(TSubclassOf<AActor> RenderClass, UTextureRenderTarget2D* RenderTarget)
{
    if (!RenderClass)
    {
        UE_LOG(LogTemp, Error, TEXT("AIconRenderActor::ExecuteRender - Invalid RenderClass"));
        return false;
    }
    if (!RenderTarget)
    {
        UE_LOG(LogTemp, Error, TEXT("AIconRenderActor::ExecuteRender - Invalid RenderTarget"));
        return false;
    }

    if (!CanCapture())
        return false;

    SpawnAndSettingsActor(RenderClass);
    CameraSettings();

    SceneCaptureComponent2D->TextureTarget = RenderTarget;
    SceneCaptureComponent2D->CaptureScene();

	if (IsValid(SpawnedActor))
		SpawnedActor->Destroy();
    SpawnedActor = nullptr;

	return true;
}

void AIconRenderActor::BeginPlay()
{
}

bool AIconRenderActor::CanCapture()
{
	if (!SceneCaptureComponent2D)
		return false;

	return true;
}

void AIconRenderActor::SpawnAndSettingsActor(TSubclassOf<AActor> ActorClass)
{
	auto World = GetWorld();
	if(!World)
		return;

	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnedActor = World->SpawnActor<AActor>(ActorClass, GetActorTransform(), ActorSpawnParameters);

	if (!IsValid(SpawnedActor))
        return;

    TArray<UPrimitiveComponent*> PrimitiveComponents;
    SpawnedActor->GetComponents<UPrimitiveComponent>(PrimitiveComponents);

    for (auto PrimitiveComponent : PrimitiveComponents)
    {
        PrimitiveComponent->LightingChannels.bChannel0 = (false);
        PrimitiveComponent->LightingChannels.bChannel1 = (true);
        PrimitiveComponent->LightingChannels.bChannel2 = (false);
    }

    SceneCaptureComponent2D->ShowOnlyActors.Add(SpawnedActor);
}

void AIconRenderActor::CameraSettings()
{


}

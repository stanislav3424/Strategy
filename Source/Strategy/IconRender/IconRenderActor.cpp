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
}

bool AIconRenderActor::ExecuteRender(TSubclassOf<AActor> RenderClass, UTextureRenderTarget2D* RenderTarget)
{
	return false;
}

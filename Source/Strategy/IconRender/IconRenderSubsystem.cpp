// Fill out your copyright notice in the Description page of Project Settings.

#include "IconRenderSubsystem.h"
#include "IconRenderActor.h"
#include "Engine/TextureRenderTarget2D.h"

void UIconRenderSubsystem::RequestIcon(AActor* Requester, TSubclassOf<AIconRenderActor> IconRenderActorClass, TSubclassOf<AActor> RenderClass, FOnIconReady Callback)
{
    auto& IconRenderInfo = IconRenderInfos.FindOrAdd(IconRenderActorClass);

    if(auto CachedIcon = IconRenderInfo.CachedIcons.Find(RenderClass))
    {
        Callback.ExecuteIfBound(*CachedIcon);
        return;
    }

	IconRenderInfo.QueueRenderClasses.FindOrAdd(RenderClass).Callbacks.Add(Requester, Callback);
}

void UIconRenderSubsystem::Tick()
{
    TSubclassOf<AIconRenderActor> SelectedIconRenderActorClass = nullptr;
    TSubclassOf<AActor> SelectedRenderClass = nullptr;

    for (auto& IconRenderInfosPair : IconRenderInfos)
    {
        for (auto& RenderClass : IconRenderInfosPair.Value.QueueRenderClasses)
        {
            SelectedIconRenderActorClass = IconRenderInfosPair.Key;
            SelectedRenderClass = RenderClass.Key;
            break;
        }

        if (SelectedIconRenderActorClass)
            break;
    }

    if (!SelectedIconRenderActorClass)
        return;

    ExecuteRender(SelectedIconRenderActorClass, SelectedRenderClass);
}

void UIconRenderSubsystem::ExecuteRender(TSubclassOf<AIconRenderActor> IconRenderActorClass, TSubclassOf<AActor> RenderClass)
{
	auto& IconRenderInfo = IconRenderInfos.FindOrAdd(IconRenderActorClass);
	if (!IsValid(IconRenderInfo.IconRenderActor))
	{
		if (auto World = GetWorld())
			World->SpawnActor(IconRenderActorClass);	
		return;
	}

	auto RenderTarget = NewObject<UTextureRenderTarget2D>();
	if (!RenderTarget)
		return;

	RenderTarget->InitAutoFormat(256, 256);

	if(IconRenderInfo.IconRenderActor->ExecuteRender(RenderClass, RenderTarget))
		AddIcon(IconRenderActorClass, RenderClass, RenderTarget);
}

void UIconRenderSubsystem::AddIcon(TSubclassOf<AIconRenderActor> IconRenderActorClass, TSubclassOf<AActor> RenderClass, UTexture* Icon)
{
	auto& IconRenderInfo = IconRenderInfos.FindOrAdd(IconRenderActorClass);

	IconRenderInfo.QueueRenderClasses.Remove(RenderClass);
	IconRenderInfo.CachedIcons.Add(RenderClass, Icon);
}
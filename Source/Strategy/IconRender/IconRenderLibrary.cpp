// Fill out your copyright notice in the Description page of Project Settings.

#include "IconRenderLibrary.h"
#include "Engine/GameInstance.h"
#include "CheckFieldMacros.h"

int32 UIconRenderLibrary::RequestIcon(UObject* WorldContextObject,
    TSubclassOf<class AIconRenderActor> IconRenderActorClass,
    TSubclassOf<AActor> RenderClass, FOnIconReady Callback)
{
    CHECK_FIELD_RETURN_VAL(LogTemp, WorldContextObject, INDEX_NONE);
    CHECK_FIELD_RETURN_VAL(LogTemp, IconRenderActorClass, INDEX_NONE);
    CHECK_FIELD_RETURN_VAL(LogTemp, RenderClass, INDEX_NONE);
    if (auto World = WorldContextObject->GetWorld())
        if (auto IconRenderSubsystem = UGameInstance::GetSubsystem<UIconRenderSubsystem>(World->GetGameInstance()))
            return IconRenderSubsystem->RequestIcon(IconRenderActorClass, RenderClass, Callback);

    return INDEX_NONE;
}

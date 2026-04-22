// Fill out your copyright notice in the Description page of Project Settings.

#include "IconRenderLibrary.h"
#include "Engine/GameInstance.h"
#include "CheckFieldMacros.h"

void UIconRenderLibrary::RequestIcon(UObject* Requester, TSubclassOf<class AIconRenderActor> IconRenderActorClass,
    TSubclassOf<AActor> RenderClass, FOnIconReady Callback)
{

    CHECK_FIELD_RETURN(LogTemp, Requester);
    CHECK_FIELD_RETURN(LogTemp, IconRenderActorClass);
    CHECK_FIELD_RETURN(LogTemp, RenderClass);
    if (auto World = Requester->GetWorld())
        if (auto IconRenderSubsystem = UGameInstance::GetSubsystem<UIconRenderSubsystem>(World->GetGameInstance()))
            IconRenderSubsystem->RequestIcon(Requester, IconRenderActorClass, RenderClass, Callback);
}

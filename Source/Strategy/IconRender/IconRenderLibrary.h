// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IconRenderSubsystem.h"
#include "IconRenderLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STRATEGY_API UIconRenderLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Requester"))
    static void RequestIcon(UObject* Requester, TSubclassOf<class AIconRenderActor> IconRenderActorClass,
        TSubclassOf<AActor> RenderClass, FOnIconReady Callback);
};

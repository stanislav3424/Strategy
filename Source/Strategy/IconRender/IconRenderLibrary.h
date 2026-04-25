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

    // Return Request ID
    // Return 0 synchronous
    // Return n asynchronous
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
    static int32 RequestIcon(UObject* WorldContextObject, TSubclassOf<class AIconRenderActor> IconRenderActorClass,
        TSubclassOf<AActor> RenderClass, FOnIconReady Callback);
};

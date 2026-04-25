// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "IconRenderSubsystem.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnIconReady, UTexture*, Icon, int32, RequestId);

USTRUCT(BlueprintType)
struct FPendingCallbacks
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Debug")
	int32 LastRequestId = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Debug")
    TMap<int32, FOnIconReady> Callbacks;
    ;
};

USTRUCT(BlueprintType)
struct FIconRenderInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Debug")
    class AIconRenderActor* IconRenderActor = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Debug")
	TMap<TSubclassOf<AActor>, UTexture*> CachedIcons;

	UPROPERTY(BlueprintReadOnly, Category = "Debug")
	TMap<TSubclassOf<AActor>, FPendingCallbacks> QueueRenderClasses;
};

/**
 *
 */
UCLASS()
class STRATEGY_API UIconRenderSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	friend class UIconRenderTickableWorldSubsystem;

public:

	// Return Request ID
    // Return 0 synchronous
    // Return n asynchronous
	UFUNCTION(BlueprintCallable)
    int32 RequestIcon(TSubclassOf<class AIconRenderActor> IconRenderActorClass,
        TSubclassOf<AActor> RenderClass, FOnIconReady Callback);

private:
	void Tick();
    void ExecuteRender(TSubclassOf<class AIconRenderActor> IconRenderActorClass, TSubclassOf<AActor> RenderClass);
    void AddIcon(
        TSubclassOf<class AIconRenderActor> IconRenderActorClass, TSubclassOf<AActor> RenderClass, UTexture* Icon);

	UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TMap<TSubclassOf<class AIconRenderActor>, FIconRenderInfo> IconRenderInfos;

};

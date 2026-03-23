// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "IconRenderSubsystem.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnIconReady, UTexture*, Icon);

class AIconRenderActor;

USTRUCT(BlueprintType)
struct FPendingCallbacks
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Debug")
	TMap<AActor*, FOnIconReady> Callbacks;
};

USTRUCT(BlueprintType)
struct FIconRenderInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Debug")
	AIconRenderActor* IconRenderActor = nullptr;

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

public:
	UFUNCTION(BlueprintCallable)
	void RequestIcon(AActor* Requester,  TSubclassOf<AIconRenderActor> IconRenderActorClass, TSubclassOf<AActor> RenderClass, FOnIconReady Callback);

private:
	void Tick();
	void ExecuteRender(TSubclassOf<AIconRenderActor> IconRenderActorClass, TSubclassOf<AActor> RenderClass);
	void AddIcon(TSubclassOf<AIconRenderActor> IconRenderActorClass, TSubclassOf<AActor> RenderClass, UTexture* Icon);

	UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	TMap<TSubclassOf<AIconRenderActor>, FIconRenderInfo> IconRenderInfos;

};

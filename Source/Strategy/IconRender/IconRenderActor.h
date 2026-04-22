// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IconRenderActor.generated.h"

class USceneCaptureComponent2D;
class UTextureRenderTarget2D;
class USpringArmComponent;

/**
 *
 */
UCLASS(Blueprintable,Abstract)
class STRATEGY_API AIconRenderActor : public AActor
{
	GENERATED_BODY()

public:
	AIconRenderActor();

	bool ExecuteRender(TSubclassOf<AActor> RenderClass, UTextureRenderTarget2D* RenderTarget);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneCaptureComponent2D* SceneCaptureComponent2D;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

private:
	bool CanCapture();
	void SpawnAndSettingsActor(TSubclassOf<AActor> ActorClass);
	void CameraSettings();

	UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	AActor* SpawnedActor;
};

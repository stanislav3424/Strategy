// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UnitFactoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQueueChanged);

class USphereComponent;

UCLASS(ClassGroup = (UnitComponent))
class STRATEGY_API UUnitFactoryComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UUnitFactoryComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void AddQueue(TSubclassOf<AActor> UnitClass);

	UFUNCTION(BlueprintCallable)
    void RemoveIndexInQueue(int32 Index);

	UFUNCTION(BlueprintCallable)
    void RemoveAllQueue();

	UFUNCTION(BlueprintCallable)
    void SetRepeatQueue(bool bRepeat);

	UFUNCTION(BlueprintCallable)
    TArray<TSubclassOf<AActor>> const& GetQueue() const { return QueueSpawnUnitClasses; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = "Unit Factory")
	USphereComponent* SpawnPoint;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = "Unit Factory")
    USphereComponent* MovePoint;

	UPROPERTY(BlueprintAssignable)
    FOnQueueChanged OnQueueChanged;

private:
    void CheckQueue();

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TArray<TSubclassOf<AActor>> CanSpawnUnitClasses;

	UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TArray<TSubclassOf<AActor>> QueueSpawnUnitClasses;
	
	UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AActor> CurrentSpawnUnitClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    bool bRepeatQueue = false;

	UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    float SpawnTimeMultiplier = 1.f;

	UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    float SpawnTime = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    float CurrentSpawnTime = 0.f;
};

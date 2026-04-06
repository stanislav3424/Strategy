// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ComponentInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UComponentInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * Interface for getting components from actors
 */
class IComponentInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Components")
    class UCommandComponent* GetCommandComponent();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Components")
    class USpawnComponent* GetSpawnComponent();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Components")
    class UTeamComponent* GetTeamComponent();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Components")
    class UArmorComponent* GetArmorComponent();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Components")
    class UUnitFactoryComponent* GetUnitFactoryComponent();
};

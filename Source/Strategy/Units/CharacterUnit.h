// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterUnit.generated.h"

UCLASS(Blueprintable, Abstract)
class STRATEGY_API ACharacterUnit : public ACharacter
{
	GENERATED_BODY()

public:
    ACharacterUnit();

    UFUNCTION(BlueprintCallable, Category = "UnitComponent")
    class USpawnComponent* GetSpawnComponent() const { return SpawnComponent; }

    UFUNCTION(BlueprintCallable, Category = "UnitComponent")
    class UTeamComponent* GetTeamComponent() const { return TeamComponent; }

    UFUNCTION(BlueprintCallable, Category = "UnitComponent")
    class UArmorComponent* GetArmorComponent() const { return ArmorComponent; }

    UFUNCTION(BlueprintCallable, Category = "UnitComponent")
    class UAICommandQueueComponent* GetAICommandQueueComponent() const { return AICommandQueueComponent; }

    UFUNCTION(BlueprintCallable, Category = "UnitComponent")
    class USelectionComponent* GetSelectionComponent() const { return SelectionComponent; }

    UFUNCTION(BlueprintCallable, Category = "UnitComponent")
    class UPathSplineComponent* GetPathSplineComponent() const { return PathSplineComponent; }

    UFUNCTION(BlueprintCallable, Category = "UnitComponent")
    class UStaticMeshComponent* GetSelectionMesh() const { return SelectionMesh; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USpawnComponent* SpawnComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UTeamComponent* TeamComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UArmorComponent* ArmorComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UAICommandQueueComponent* AICommandQueueComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USelectionComponent* SelectionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UPathSplineComponent* PathSplineComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* SelectionMesh;
};

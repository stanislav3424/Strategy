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

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    //class UPathDrawingComponent* PathDrawingComponent;
};

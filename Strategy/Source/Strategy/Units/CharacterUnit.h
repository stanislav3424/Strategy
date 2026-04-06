// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ComponentInterface.h"
#include "CharacterUnit.generated.h"

UCLASS()
class STRATEGY_API ACharacterUnit : public ACharacter, public IComponentInterface
{
	GENERATED_BODY()

public:
	ACharacterUnit();

    virtual class UCommandComponent* GetCommandComponent_Implementation() override;
    virtual class USpawnComponent*   GetSpawnComponent_Implementation() override;
    virtual class UTeamComponent*    GetTeamComponent_Implementation() override;
    virtual class UArmorComponent*   GetArmorComponent_Implementation() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USpawnComponent* SpawnComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UTeamComponent* TeamComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UArmorComponent* ArmorComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UUnitCommandComponent* UnitCommandComponent;
};

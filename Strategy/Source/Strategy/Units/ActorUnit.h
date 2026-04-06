// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ComponentInterface.h"
#include "ActorUnit.generated.h"

UCLASS()
class STRATEGY_API AActorUnit : public AActor, public IComponentInterface
{
	GENERATED_BODY()
	
public:
    AActorUnit();

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
};

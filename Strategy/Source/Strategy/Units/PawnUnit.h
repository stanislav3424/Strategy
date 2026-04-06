// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ComponentInterface.h"
#include "PawnUnit.generated.h"

UCLASS()
class STRATEGY_API APawnUnit : public APawn, public IComponentInterface
{
	GENERATED_BODY()

public:
	APawnUnit();

    virtual class UCommandComponent* GetCommandComponent_Implementation() override;
    virtual class USpawnComponent*   GetSpawnComponent_Implementation() override;
    virtual class UTeamComponent*    GetTeamComponent_Implementation() override;
    virtual class UArmorComponent*   GetArmorComponent_Implementation() override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USpawnComponent* SpawnComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UTeamComponent* TeamComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UArmorComponent* ArmorComponent;	
};

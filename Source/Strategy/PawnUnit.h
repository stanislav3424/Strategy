// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnUnit.generated.h"

class USpawnComponent;
class UTeamComponent;
class UArmorComponent;
class UBehaviorTreeComponent;
class UBlackboardComponent;
class UBehaviorTree;

UCLASS()
class STRATEGY_API APawnUnit : public APawn
{
	GENERATED_BODY()

public:
	APawnUnit();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpawnComponent* SpawnComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UTeamComponent* TeamComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UArmorComponent* ArmorComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBehaviorTreeComponent* BehaviorTreeComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBlackboardComponent* BlackboardComponent;
};

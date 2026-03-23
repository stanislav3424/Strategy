// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterUnit.generated.h"

class USpawnComponent;
class UTeamComponent;
class UArmorComponent;
class UBehaviorTreeComponent;
class UBlackboardComponent;
class UBehaviorTree;

UENUM(BlueprintType)
enum class EUnitCommand : uint8
{
    None,
    Default,
    AttackUnit,
    MoveTo,
    Assault,
};

UCLASS()
class STRATEGY_API ACharacterUnit : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterUnit();

    UFUNCTION(BlueprintCallable, Category = "Commands")
    void CancelCommand();

    UFUNCTION(BlueprintCallable, Category = "Commands")
    void CommandAttackUnit(AActor* TargetUnit);

    UFUNCTION(BlueprintCallable, Category = "Commands")
    void CommandMoveTo(FVector const& Destination);

    UFUNCTION(BlueprintCallable, Category = "Commands")
    void CommandAssault(FVector const& Destination);

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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    TMap<EUnitCommand, UBehaviorTree*> BehaviorTrees;

};

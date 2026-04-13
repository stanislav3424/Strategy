// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageProcessor.generated.h"

class UArmorComponent;

/**
 * 
 */
UCLASS(Abstract)
class STRATEGY_API UDamageProcessor : public UDamageType
{
    GENERATED_BODY()

public:
    void ExecuteDamage(float Damage, UArmorComponent* ArmorComponent) const;
};

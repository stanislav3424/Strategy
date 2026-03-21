// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageProcessor.h"
#include "ArmorComponent.h"

void UDamageProcessor::ExecuteDamage(float Damage, UArmorComponent* ArmorComponent) const
{
    if (!ArmorComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("UDamageProcessor::ExecuteDamage - ArmorComponent is null!"));
        return;
    }

    ArmorComponent->ApplyDamageHealthIncludingArmor(Damage, 0.f, 0.f);
}

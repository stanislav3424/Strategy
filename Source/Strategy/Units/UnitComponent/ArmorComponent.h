// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArmorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, CurrentHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArmorChanged, float, CurrentArmor, float, MaxArmor);

UCLASS(ClassGroup = (UnitComponent), meta = (BlueprintSpawnableComponent))
class STRATEGY_API UArmorComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    float GetCurrentHealth() const { return CurrentHealth; };
    float GetMaxHealth() const { return MaxHealth; };
    float GetCurrentArmorDurability() const { return CurrentArmorDurability; };
    float GetMaxArmorDurability() const { return MaxArmorDurability; };
    float GetArmorRating() const { return ArmorRating; };
    float GetRemainingArmorEffectiveness() const { return CurrentArmorDurability / MaxArmorDurability * ArmorRating; };

    UFUNCTION(BlueprintCallable)
    void ApplyDamageHealthIncludingArmor(float DamageHealth, float DamageArmor, float PunchingArmorEffectiveness);

    UPROPERTY(BlueprintAssignable)
    FOnHealthChanged OnHealthChanged;

    UPROPERTY(BlueprintAssignable)
    FOnArmorChanged OnArmorChanged;

    UFUNCTION(BlueprintCallable)
    void BroadcastHealthChanged() const { OnHealthChanged.Broadcast(CurrentHealth, MaxHealth); }

    UFUNCTION(BlueprintCallable)
    void BroadcastArmorChanged() const { OnArmorChanged.Broadcast(CurrentArmorDurability, MaxArmorDurability); }

protected:
    virtual void BeginPlay() override;

private:
    void ApplyDamageHealth(float Damage);
    void ApplyDamageArmor(float Damage);

    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
        AActor* DamageCauser);

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    float MaxHealth;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    float CurrentHealth;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    float MaxArmorDurability;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    float CurrentArmorDurability;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    float ArmorRating;
};

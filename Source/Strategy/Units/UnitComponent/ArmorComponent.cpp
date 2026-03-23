// Fill out your copyright notice in the Description page of Project Settings.

#include "ArmorComponent.h"
#include "DamageProcessor.h"

void UArmorComponent::ApplyDamageHealthIncludingArmor(
    float DamageHealth, float DamageArmor, float PunchingArmorEffectiveness)
{
    ApplyDamageArmor(DamageArmor);
    const float ArmorEffectiveness = GetRemainingArmorEffectiveness();
    const float DamageMultiplier   = PunchingArmorEffectiveness > ArmorEffectiveness ? 1.0f : 0.0f;
    const float RealDamageHealth   = DamageHealth * DamageMultiplier;
    ApplyDamageHealth(RealDamageHealth);
}

void UArmorComponent::BeginPlay()
{
	Super::BeginPlay();

	auto Owner = GetOwner();
    if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("UArmorComponent::BeginPlay - UArmorComponent has no owner!"));
		return;
	}

	Owner->OnTakeAnyDamage.AddDynamic(this, &UArmorComponent::OnTakeAnyDamage);

    if (MaxHealth <= 0.f)
    {
        MaxHealth = 100.f;
        UE_LOG(LogTemp, Warning, TEXT("UArmorComponent::BeginPlay - MaxHealth is non-positive for %s!"), *GetOwner()->GetName());
    }
    if (MaxArmorDurability < 0.f)
    {
        MaxArmorDurability = 0.f;
        UE_LOG(LogTemp, Warning, TEXT("UArmorComponent::BeginPlay - MaxArmorDurability is negative for %s!"), *GetOwner()->GetName());
    }
    if (ArmorRating < 0.f)
    {
        ArmorRating = 0.f;
        UE_LOG(LogTemp, Warning, TEXT("UArmorComponent::BeginPlay - ArmorRating is negative for %s!"), *GetOwner()->GetName());
    }
}

void UArmorComponent::ApplyDamageHealth(float Damage)
{
    if (Damage <= 0.f)
    {
        UE_LOG(LogTemp, Error, TEXT("UArmorComponent::ApplyDamageHealth - Damage is non-positive!"));
        return;
    }

    CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
    BroadcastHealthChanged();

    if (CurrentHealth <= 0.f)
    {

    }
}

void UArmorComponent::ApplyDamageArmor(float Damage)
{
    if (Damage <= 0.f)
    {
        UE_LOG(LogTemp, Error, TEXT("UArmorComponent::ApplyDamageArmor - Damage is non-positive!"));
        return;
    }

    CurrentArmorDurability = FMath::Clamp(CurrentArmorDurability - Damage, 0.f, MaxArmorDurability);
    BroadcastArmorChanged();
}

void UArmorComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	auto DamageProcessor = Cast<UDamageProcessor>(DamageType);
	if (!DamageProcessor)
	{
		UE_LOG(LogTemp, Error, TEXT("UArmorComponent::OnTakeAnyDamage - DamageType is not a UDamageProcessor!"));
		return;
	}
    DamageProcessor->ExecuteDamage(Damage, this);

}
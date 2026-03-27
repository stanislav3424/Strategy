// Fill out your copyright notice in the Description page of Project Settings.

#include "Units/ActorUnit.h"
#include "SpawnComponent.h"
#include "TeamComponent.h"
#include "ArmorComponent.h"
#include "Turret.h"

AActorUnit::AActorUnit()
{
    SpawnComponent       = CreateDefaultSubobject<USpawnComponent>(TEXT("SpawnComponent"));
    TeamComponent        = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
    ArmorComponent       = CreateDefaultSubobject<UArmorComponent>(TEXT("ArmorComponent"));

}

UCommandComponent* AActorUnit::GetCommandComponent_Implementation()
{
    return nullptr;
}

USpawnComponent* AActorUnit::GetSpawnComponent_Implementation()
{
    return SpawnComponent;
}

UTeamComponent* AActorUnit::GetTeamComponent_Implementation()
{
    return TeamComponent;
}

UArmorComponent* AActorUnit::GetArmorComponent_Implementation()
{
    return ArmorComponent;
}

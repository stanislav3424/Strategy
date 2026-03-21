// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitFactoryComponent.h"
#include "Components/SphereComponent.h"
#include "SpawnComponent.h"

UUnitFactoryComponent::UUnitFactoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SpawnPoint = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnPoint"));
    SpawnPoint->SetupAttachment(this);
    SpawnPoint->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));
    SpawnPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MovePoint = CreateDefaultSubobject<USphereComponent>(TEXT("MovePoint"));
    MovePoint->SetupAttachment(this);
    MovePoint->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));
    MovePoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UUnitFactoryComponent::BeginPlay()
{
    Super::BeginPlay();

    if (CanSpawnUnitClasses.IsEmpty())
    {
        UE_LOG(LogTemp, Warning,
            TEXT("UUnitFactoryComponent::BeginPlay - No unit classes specified in CanSpawnUnitClasses. This "
                 "factory will not be able to spawn any units."));
    }

    for (auto UnitClass : CanSpawnUnitClasses)
    {
        if (!UnitClass)
        {
            UE_LOG(LogTemp, Warning,
                TEXT("UUnitFactoryComponent::BeginPlay - Invalid unit class found in CanSpawnUnitClasses. This "
                     "factory will not be able to spawn this unit."));
        }
    }
}

void UUnitFactoryComponent::AddQueue(TSubclassOf<AActor> UnitClass)
{
    if (!UnitClass)
    {
        UE_LOG(LogTemp, Error, TEXT("UUnitFactoryComponent::AddQueue - Invalid unit class provided."));
        return;
    }

    if (!CanSpawnUnitClasses.Contains(UnitClass))
    {
        UE_LOG(LogTemp, Error, TEXT("UUnitFactoryComponent::AddQueue - Unit class %s cannot be spawned by this factory."), *UnitClass->GetName());
        return;
    }

    QueueSpawnUnitClasses.Add(UnitClass);

    CheckQueue();
    OnQueueChanged.Broadcast();
}

void UUnitFactoryComponent::RemoveIndexInQueue(int32 Index)
{
    if (!QueueSpawnUnitClasses.IsValidIndex(Index))
        return;

    QueueSpawnUnitClasses.RemoveAt(Index);

    CheckQueue();
    OnQueueChanged.Broadcast();
}

void UUnitFactoryComponent::RemoveAllQueue()
{
    if (QueueSpawnUnitClasses.IsEmpty())
        return;

    CheckQueue();
    OnQueueChanged.Broadcast();
}

void UUnitFactoryComponent::SetRepeatQueue(bool bRepeat)
{
}

void UUnitFactoryComponent::CheckQueue()
{
    if (QueueSpawnUnitClasses.IsEmpty())
    {
        CurrentSpawnUnitClass = nullptr;
        SpawnTime             = 0.f;
        CurrentSpawnTime      = 0.f;
        return;
    }

    if (CurrentSpawnUnitClass && CurrentSpawnUnitClass == QueueSpawnUnitClasses[0])
    {
        return;
    }
    else
    {
        CurrentSpawnUnitClass = nullptr;
        SpawnTime             = 0.f;
        CurrentSpawnTime      = 0.f;
    }

    if (!CurrentSpawnUnitClass)
    {
        CurrentSpawnUnitClass = QueueSpawnUnitClasses[0];
        if (auto DefaultObject = CurrentSpawnUnitClass->GetDefaultObject<AActor>())
        {
            if (auto SpawnComponent = DefaultObject->FindComponentByClass<USpawnComponent>())
            {
                SpawnTime = SpawnComponent->GetSpawnTime();
            }
            else
            {
                UE_LOG(LogTemp, Error,
                    TEXT("UUnitFactoryComponent::CheckQueue - No SpawnComponent found on default object of unit class "
                         "%s. This factory will not be able to spawn this unit."),
                    *CurrentSpawnUnitClass->GetName());
            }
        }
        CurrentSpawnTime = 0.f;
    }
}

void UUnitFactoryComponent::TickComponent(
    float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CheckQueue();
}

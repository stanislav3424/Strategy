// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

/**
 *
 */
UCLASS(Blueprintable, Abstract)
class STRATEGY_API AGamePlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AGamePlayerController();

    bool         IsSelection() const { return bIsSelection; }
    FVector      GetStartSelectionLocation() const { return StartSelectionLocation; }
    FVector      GetEndSelectionLocation() const { return EndSelectionLocation; }
    void         UpdateSelectionActors(TArray<AActor*> const& NewSelectedActors);
    AActor*      GetActorUnderMouseCursor() const;
    FVector      GetMouseWorldLocation() const;
    virtual void Tick(float DeltaSeconds) override;

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    void OnSelectionStarted(struct FInputActionValue const& InputAction);
    void OnSelectionCompleted(struct FInputActionValue const& InputAction);
    void OnCommand(struct FInputActionValue const& InputAction);

    UPROPERTY(EditDefaultsOnly, Category = "Imput")
    class UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Imput")
    class UInputAction* SelectionAction;

    UPROPERTY(EditDefaultsOnly, Category = "Imput")
    class UInputAction* CommandAction;

private:
    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    bool bIsSelection = false;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    bool bIsDetectSelection = false;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    FVector StartSelectionLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    FVector EndSelectionLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TSet<AActor*> SelectedActors;

    UPROPERTY(EditDefaultsOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    float DistanceThreshold = 25.f;

    UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UCommandObject> CurrentCommand;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera.generated.h"

UCLASS()
class STRATEGY_API ACamera : public APawn
{
	GENERATED_BODY()

public:
    ACamera();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

    void OnMoveCamera(struct FInputActionValue const& InputAction);
    void OnRotateCamera(struct FInputActionValue const& InputAction);
    void OnZoomCamera(struct FInputActionValue const& InputAction);

	UPROPERTY(EditDefaultsOnly, Category = "Imput")
    class UInputMappingContext* MoveCameraMappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Imput")
    class UInputAction* MoveCameraAction;

    UPROPERTY(EditDefaultsOnly, Category = "Imput")
    class UInputAction* RotateCameraAction;

    UPROPERTY(EditDefaultsOnly, Category = "Imput")
    class UInputAction* ZoomCameraAction;

    UPROPERTY(VisibleAnywhere, Category = "Camera")
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, Category = "Camera")
    class UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere, Category = "Camera")
    class UPawnMovementComponent* FloatingPawnMovement;
};

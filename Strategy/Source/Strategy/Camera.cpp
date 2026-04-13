// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera.h"
#include "CheckFieldMacros.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

ACamera::ACamera()
{
    auto Root     = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->bDoCollisionTest         = false;
    SpringArm->bEnableCameraLag         = true;
    SpringArm->bEnableCameraRotationLag = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

    FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

void ACamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (!EnhancedInputComponent)
        return;

    CHECK_FIELD_RETURN(LogTemp, MoveCameraAction);
    EnhancedInputComponent->BindAction(MoveCameraAction, ETriggerEvent::Triggered, this, &ACamera::OnMoveCamera);

    CHECK_FIELD_RETURN(LogTemp, RotateCameraAction);
    EnhancedInputComponent->BindAction(RotateCameraAction, ETriggerEvent::Triggered, this, &ACamera::OnRotateCamera);

    CHECK_FIELD_RETURN(LogTemp, ZoomCameraAction);
    EnhancedInputComponent->BindAction(ZoomCameraAction, ETriggerEvent::Triggered, this, &ACamera::OnZoomCamera);
}

void ACamera::BeginPlay()
{
    Super::BeginPlay();

    CHECK_FIELD_RETURN(LogTemp, MoveCameraMappingContext);
    auto World = GetWorld();
    if (!World)
        return;
    auto LocalPlayer = World->GetFirstLocalPlayerFromController();
    if (!LocalPlayer)
        return;
    auto EnhancedInputLocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    if (!EnhancedInputLocalPlayerSubsystem)
        return;
    EnhancedInputLocalPlayerSubsystem->AddMappingContext(MoveCameraMappingContext, 0);
}

void ACamera::OnMoveCamera(FInputActionValue const& InputAction)
{
    auto const Value = InputAction.Get<FVector2D>();
    if (Value.IsNearlyZero())
        return;

    AddMovementInput(GetActorForwardVector(), Value.X);
    AddMovementInput(GetActorRightVector(), Value.Y);
}

void ACamera::OnRotateCamera(FInputActionValue const& InputAction)
{
    auto const Value = InputAction.Get<float>();
    if(FMath::IsNearlyZero(Value)) return;

    AddControllerYawInput(Value);
}

void ACamera::OnZoomCamera(FInputActionValue const& InputAction)
{
    auto const Value = InputAction.Get<float>();
    if(FMath::IsNearlyZero(Value)) return;

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Remove Control Rotation from Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Collider"));
	RootComponent = RootComp;

	//Camera Setup
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 300.f;
	CameraSpringArm->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false;
	
	//Movement Setup
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));

	//Vehicle Setup
	VehicleTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Vehicle Trigger"));
	VehicleTrigger->SetGenerateOverlapEvents(true);
	VehicleTrigger->SetupAttachment(RootComponent);

	VehicleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VehicleMesh"));
	VehicleMesh->SetupAttachment(VehicleTrigger);

	Lives = 3;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* _PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* _SS = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(_PC->GetLocalPlayer()))
		{
			_SS->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* _EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		_EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPawn::Move);

		_EIC->BindAction(PowerUpAction, ETriggerEvent::Triggered, this, &APlayerPawn::PowerUp);
	}

}

void APlayerPawn::Move(const FInputActionValue& InputVal)
{
	FVector2D MovementVector = InputVal.Get<FVector2D>();
	AddMovementInput(FVector(0, MovementVector.X, MovementVector.Y), MoveSpeed);
}

void APlayerPawn::PowerUp(const FInputActionValue& InputVal)
{
	PowerUpSlot->UsePowerUp();
}

void APlayerPawn::RegisterHit()
{
	--Lives;
	if (Lives <= 0)
	{
		EndGame();
	}
}
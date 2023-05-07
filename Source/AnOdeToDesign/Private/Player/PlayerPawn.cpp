// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Destroyables/Destroyable.h"
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


	//Vehicle Setup
	Vehicle1Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Vehicle 1 Trigger"));
	Vehicle1Trigger->SetGenerateOverlapEvents(true);
	Vehicle1Trigger->SetupAttachment(RootComponent);

	Vehicle2Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Vehicle 2 Trigger"));
	Vehicle2Trigger->SetGenerateOverlapEvents(true);
	Vehicle2Trigger->SetupAttachment(RootComponent);

	Vehicle1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Vehicle 1 Mesh"));
	Vehicle1Mesh->SetupAttachment(Vehicle1Trigger);

	Vehicle2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Vehicle 2 Mesh"));
	Vehicle2Mesh->SetupAttachment(Vehicle2Trigger);

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
		_EIC->BindAction(MoveAction1, ETriggerEvent::Triggered, this, &APlayerPawn::MovePlayer1);
		_EIC->BindAction(MoveAction2, ETriggerEvent::Triggered, this, &APlayerPawn::MovePlayer2);
	}

}

void APlayerPawn::MovePlayer1(const FInputActionValue& InputVal)
{
	FVector2D MovementVector = InputVal.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("Actor 1 location: %s"), *MovementVector.ToString());
	float x = FMath::Clamp(Vehicle1Trigger->GetRelativeLocation().Y + ((MovementVector.X) * MoveSpeed * GetWorld()->GetDeltaSeconds()), -BoundaryValues.X, BoundaryValues.X);
	float y = FMath::Clamp(Vehicle1Trigger->GetRelativeLocation().Z + ((MovementVector.Y) * MoveSpeed * GetWorld()->GetDeltaSeconds()), -BoundaryValues.Y, BoundaryValues.Y);
	Vehicle1Trigger->SetRelativeLocation(FVector(Vehicle1Trigger->GetRelativeLocation().X, x, y), true);
}

void APlayerPawn::MovePlayer2(const FInputActionValue& InputVal)
{
	FVector2D MovementVector = InputVal.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("Actor 2 location: %s"), *MovementVector.ToString());
	float x = FMath::Clamp(Vehicle2Trigger->GetRelativeLocation().Y + ((MovementVector.X) * MoveSpeed * GetWorld()->GetDeltaSeconds()), -BoundaryValues.X, BoundaryValues.X);
	float y = FMath::Clamp(Vehicle2Trigger->GetRelativeLocation().Z + ((MovementVector.Y) * MoveSpeed * GetWorld()->GetDeltaSeconds()), -BoundaryValues.Y, BoundaryValues.Y);
	Vehicle2Trigger->SetRelativeLocation(FVector(Vehicle2Trigger->GetRelativeLocation().X, x, y) , true);
}

void APlayerPawn::RegisterHit()
{
	--Lives;
	if (Lives <= 0)
	{
		EndGame();
	}
}


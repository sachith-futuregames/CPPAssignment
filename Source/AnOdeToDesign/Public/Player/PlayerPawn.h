// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pickups/PowerUps.h"
#include "PlayerPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UFloatingPawnMovement;
class USkeletalMeshComponent;
class USceneComponent;
class UBoxComponent;
struct FInputActionValue;
//
UCLASS(config = Game)
class ANODETODESIGN_API APlayerPawn : public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	/*Core Utils*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void EndGame();

	UFUNCTION(BlueprintCallable)
	void RegisterHit();
private:
	/*Camera Components*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;

	/*Input Contexts*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction* PowerUpAction;

	/*Movement Component*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector2D BoundaryValues;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* VehicleTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* MovementComponent;

	/*Powerups*/
	TScriptInterface<IPowerUps> PowerUpSlot;

	/*Aesthetics*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* VehicleMesh;

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Called when Move Inputs are received
	UFUNCTION()
	void Move(const FInputActionValue& InputVal);
	//Called when Powerup Inputs are received
	UFUNCTION()
	void PowerUp(const FInputActionValue& InputVal);

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, meta = (AllowPrivateAccess = "true"))
	int Lives;
};

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
class UStaticMeshComponent;
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
	UInputAction* MoveAction1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction2;

	/*Movement Component*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector2D BoundaryValues;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Vehicle1Trigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Vehicle2Trigger;

	/*Aesthetics*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Vehicle1Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Vehicle2Mesh;



public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int index;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	UFUNCTION(BlueprintCallable)
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Called when Move Inputs are received
	UFUNCTION()
	void MovePlayer1(const FInputActionValue& InputVal);

	UFUNCTION()
	void MovePlayer2(const FInputActionValue& InputVal);


	UPROPERTY(VisibleAnywhere, BlueprintReadonly, meta = (AllowPrivateAccess = "true"))
	int Lives;
};

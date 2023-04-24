// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/LevelManager.h"
#include "Components/SceneComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SpawnPoint;
	BlockCount = 15;
	for (int i = 0; i < BlockCount; ++i)
	{
		Blocks.Add(CreateDefaultSubobject<UStaticMeshComponent>(*FString::Printf(TEXT("Block %i"), i)));
		Blocks[i]->SetupAttachment(RootComponent);
	}
}


// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	SetMeshes();
}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (UStaticMeshComponent* Block : Blocks)
	{
		FVector Pos = Block->GetRelativeLocation();
		Pos.X -= MoveSpeed * DeltaTime;
		Block->SetRelativeLocation(Pos, true);
	}
}

void ALevelManager::SetMeshes()
{
	int i = 0;
	for (UStaticMeshComponent* Block : Blocks)
	{
		Block->SetStaticMesh(BlockMeshes[FMath::RandRange(0, BlockMeshes.Num() - 1)]);
		FVector Pos = FVector::Zero();
		Pos.X -= (Blocks.Num() - i) * MoveSpeed;
		Block->SetRelativeLocation(Pos, true);
		++i;
	}
}

void ALevelManager::ReUse(UStaticMeshComponent* InComp)
{
	InComp->SetStaticMesh(BlockMeshes[FMath::RandRange(0, BlockMeshes.Num() - 1)]);
	InComp->SetRelativeLocation(FVector::Zero(), true);
}


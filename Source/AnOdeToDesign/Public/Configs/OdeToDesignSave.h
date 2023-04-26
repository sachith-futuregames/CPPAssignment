// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "OdeToDesignSave.generated.h"

/**
 * 
 */
UCLASS()
class ANODETODESIGN_API UOdeToDesignSave : public USaveGame
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SaveIfElegible(float NewScore);

private:
	TArray<float> HighScores;
	
};

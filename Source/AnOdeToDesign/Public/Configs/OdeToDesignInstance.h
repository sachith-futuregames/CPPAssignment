// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OdeToDesignInstance.generated.h"

class UOdeToDesignSave;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ANODETODESIGN_API UOdeToDesignInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;
	virtual void Shutdown() override;

	void SaveHighScore(float InScore);


private:
	UOdeToDesignSave* SaveFile;
};

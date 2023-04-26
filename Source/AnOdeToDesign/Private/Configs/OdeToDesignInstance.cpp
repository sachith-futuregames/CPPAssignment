// Fill out your copyright notice in the Description page of Project Settings.


#include "Configs/OdeToDesignInstance.h"
#include "Configs/OdeToDesignSave.h"
#include "Kismet/GameplayStatics.h"

void UOdeToDesignInstance::Init()
{
	if (UOdeToDesignSave* LoadedGame = Cast<UOdeToDesignSave>(UGameplayStatics::LoadGameFromSlot(UTF8_TO_TCHAR("General"), 0)))
	{
		SaveFile = LoadedGame;
	}
	else
	{
		SaveFile = NewObject<UOdeToDesignSave>();
	}
}
void UOdeToDesignInstance::Shutdown()
{
	UGameplayStatics::SaveGameToSlot(SaveFile, UTF8_TO_TCHAR("General"), 0);
}

void UOdeToDesignInstance::SaveHighScore(float InScore)
{
	SaveFile->SaveIfElegible(InScore);
}
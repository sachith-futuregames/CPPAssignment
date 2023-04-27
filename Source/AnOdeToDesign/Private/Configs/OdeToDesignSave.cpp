// Fill out your copyright notice in the Description page of Project Settings.


#include "Configs/OdeToDesignSave.h"

void UOdeToDesignSave::SaveIfElegible(float NewScore)
{
	HighScores.Add(NewScore);
	HighScores.Sort([](const float& a, const float& b) { return a > b; });
	

	while (HighScores.Num() > 10)
	{
		HighScores.RemoveAt(HighScores.Num() - 1);
	}
}
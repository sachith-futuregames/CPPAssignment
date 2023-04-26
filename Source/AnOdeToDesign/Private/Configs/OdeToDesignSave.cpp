// Fill out your copyright notice in the Description page of Project Settings.


#include "Configs/OdeToDesignSave.h"

void UOdeToDesignSave::SaveIfElegible(float NewScore)
{
	if (HighScores.Num() == 0)
		HighScores.Add(NewScore);
	for (int i = 0; i < HighScores.Num(); ++i)
	{
		if (NewScore > HighScores[i])
		{
			HighScores.Insert(NewScore, i);
		}
	}

	while (HighScores.Num() > 10)
	{
		HighScores.RemoveAt(HighScores.Num() - 1);
	}
}
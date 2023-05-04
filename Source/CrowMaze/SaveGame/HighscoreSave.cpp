// Fill out your copyright notice in the Description page of Project Settings.


#include "HighscoreSave.h"

#include "CrowMaze/BPFunctionLibrary/SortingArray.h"

void UHighscoreSave::AddHighScoreValue(int HighScoreToAdd)
{
	if (HighScoreValues.IsEmpty())
	{
		HighScoreValues.Add(HighScoreToAdd);
		return;
	}
	const int ArrayIndex = USortingArray::FindInsertIndex(HighScoreValues,HighScoreToAdd);
	HighScoreValues.Insert(HighScoreToAdd,ArrayIndex);
}

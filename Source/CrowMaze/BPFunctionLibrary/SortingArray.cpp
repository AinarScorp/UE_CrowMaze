// Fill out your copyright notice in the Description page of Project Settings.


#include "SortingArray.h"

int USortingArray::FindInsertIndex(const TArray<int32>& Array, const int Key)
{
	//UE_LOG(LogTemp, Warning, TEXT("Low: %i, High: %i, Key: %i"), Low, High, Key);
	for (int i = 0; i < Array.Num(); ++i)
	{
		if (Array[i]>= Key)
		{
			return i;
		}
	}
	return Array.Num();
}


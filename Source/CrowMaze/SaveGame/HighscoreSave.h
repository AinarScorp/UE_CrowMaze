// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HighscoreSave.generated.h"

/**
 * 
 */
UCLASS()
class CROWMAZE_API UHighscoreSave : public USaveGame
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void AddHighScoreValue(int HighScoreToAdd);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<int> GetHighScoreValues() {return HighScoreValues;};
private:
	UPROPERTY()
	TArray<int> HighScoreValues;
};

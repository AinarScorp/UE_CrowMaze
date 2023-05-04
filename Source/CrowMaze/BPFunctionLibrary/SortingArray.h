// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SortingArray.generated.h"

/**
 * 
 */
UCLASS()
class CROWMAZE_API USortingArray : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Sorting Function")
	static int FindInsertIndex(UPARAM(ref) const TArray<int32> & Array, const int Key);
	
};

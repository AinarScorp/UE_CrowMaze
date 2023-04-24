// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolableActorAbstact.generated.h"

UCLASS(Abstract)
class CROWMAZE_API APoolableActorAbstact : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoolableActorAbstact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	virtual void SetLifeSpan(float InLifeTime) override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SpawnActor(const FVector& NewLocation,const FRotator& NewRotation);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetActive(bool InActive);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	bool IsActive();
	// UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	// float GetLifeSpan();
	// UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	// FTimerHandle GetLifeSpanTimerMy();
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Deactivate();

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Object Pool")
	bool bIsActive;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Object Pool")
	float LifeSpan;
	UPROPERTY(BlueprintReadWrite, Category = "Object Pool")
	FTimerHandle LifeSpanTimer;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TrapTrigger.generated.h"

UCLASS()
class CROWMAZE_API ATrapTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrapTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class ATrap* TrapToTrigger;
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxTrigger;
private:
	UFUNCTION()
	void TriggerTrap(AActor* OverlappedActor, AActor* OtherActor);

};



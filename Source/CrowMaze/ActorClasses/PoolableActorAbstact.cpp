// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolableActorAbstact.h"

// Sets default values
APoolableActorAbstact::APoolableActorAbstact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoolableActorAbstact::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoolableActorAbstact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoolableActorAbstact::SetLifeSpan(float InLifeTime)
{
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Purple, FString::Printf(TEXT("Set life span + %f"), InLifeTime) );
	LifeSpan = InLifeTime;
	if (LifeSpan>0)
	{
		GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &APoolableActorAbstact::Deactivate, LifeSpan,false);
	}
}

void APoolableActorAbstact::Deactivate_Implementation()
{
	SetActive(false);
}


bool APoolableActorAbstact::IsActive_Implementation()
{
	return bIsActive;
}

void APoolableActorAbstact::SetActive_Implementation(bool InActive)
{
	bIsActive = InActive;
	SetActorHiddenInGame(!bIsActive);
	SetActorTickEnabled(InActive);
}

void APoolableActorAbstact::SpawnActor_Implementation(const FVector& NewLocation,const FRotator& NewRotation)
{
	SetActive(true);
	SetActorLocation(NewLocation);
	SetActorRotation(NewRotation);
}


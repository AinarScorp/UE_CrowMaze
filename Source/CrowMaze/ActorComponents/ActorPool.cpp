// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPool.h"

#include "CrowMaze/ActorClasses/PoolableActorAbstact.h"
// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

UActorPool::~UActorPool()
{
	
	UE_LOG(LogTemp,Warning, TEXT("I got destroyed"))

}


// Called when the game starts
void UActorPool::BeginPlay()
{
	Super::BeginPlay();
	if (!ActorSubclassIsValid())
	{
		return;
	}

	if (GetWorld())
	{
		for (int i = 0; i < PoolSize; ++i)
		{
			SpawnActorToPool();
		}
	}
}

APoolableActorAbstact* UActorPool::GetPooledActorBP()
{
	return GetPooledActor();
}


//
// APoolableActorAbstact* UActorPool::GetPooledActorBP()
// {
// 	return GetPooledActor()->GetActorMy().Get();
// }



TObjectPtr<APoolableActorAbstact> UActorPool::GetPooledActor()
{
	
	for (TObjectPtr<APoolableActorAbstact> PoolableActor : Pool)
	{
		if (!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
		// if (!PoolableActor->Execute_IsActiveMy(PoolableActor->GetActorMy()))
		// {
		// 	return PoolableActor;
		// }
	}
	if (!ActorSubclassIsValid())
	{
		UE_LOG(LogTemp,Warning, TEXT("Tried to spawn an actor without sucess"))
		return nullptr;
	}
	UE_LOG(LogTemp,Warning, TEXT("Spawned one more"))
	return SpawnActorToPool();
}

bool UActorPool::ActorSubclassIsValid() const
{
	return ActorSubclass != nullptr;
	// if (ActorSubclass == nullptr)
	// {
	// 	return false;
	// }
	// if (!ActorSubclass->ImplementsInterface(UPoolableActor::StaticClass()))
	// {
	// 	return false;
	// }
	//return true;
}

TObjectPtr<APoolableActorAbstact> UActorPool::SpawnActorToPool()
{
	TObjectPtr<APoolableActorAbstact> SpawnedActor = GetWorld()->SpawnActor<APoolableActorAbstact>(ActorSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
	//TObjectPtr<IPoolableActor> PoolableActor =Cast<IPoolableActor>(ActorToSpawn);
	//IPoolableActor* PoolableActor = Cast<IPoolableActor>(ActorToSpawn);
	SpawnedActor->SetActive(false);
	//PoolableActor->Execute_SetActiveMy(SpawnedActor, false);
	Pool.Add(SpawnedActor);
	return SpawnedActor;
}

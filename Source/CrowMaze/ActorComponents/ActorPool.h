// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CROWMAZE_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActorPool();
	virtual ~UActorPool() override;
protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	class APoolableActorAbstact* GetPooledActorBP();
	UFUNCTION()
	bool ActorSubclassIsValid() const;
	
	TObjectPtr<class APoolableActorAbstact> GetPooledActor();
	TObjectPtr<APoolableActorAbstact> SpawnActorToPool();
		
private:
	UPROPERTY(EditAnywhere, Category = "Object Pool")
	int PoolSize = 100;
	
	UPROPERTY(EditAnywhere, Category = "Object Pool")
	TSubclassOf<class APoolableActorAbstact> ActorSubclass;
	UPROPERTY(VisibleAnywhere, Category = "Object Pool")
	TArray<TObjectPtr<class APoolableActorAbstact>> Pool;
};

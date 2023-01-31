// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapTrigger.h"

#include "Trap.h"
#include "CrowMaze/PawnClasses/Crow.h"

// Sets default values
ATrapTrigger::ATrapTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	SetRootComponent(BoxTrigger);
}

// Called when the game starts or when spawned
void ATrapTrigger::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this,&ATrapTrigger::TriggerTrap);
	
	
}

// Called every frame
void ATrapTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrapTrigger::TriggerTrap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp,Warning,TEXT("Provoked"));

	if (Cast<ACrow>(OtherActor) == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("%s is touched by non crow, I'm touched by %s"), *GetActorNameOrLabel(),*OtherActor->GetActorNameOrLabel());
		return;
	}
	if (TrapToTrigger != nullptr)
	{
		TrapToTrigger->ProvokeTrap();
	}
}


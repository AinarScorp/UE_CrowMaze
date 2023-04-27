// Fill out your copyright notice in the Description page of Project Settings.


#include "CrowAttributes.h"

// Sets default values for this component's properties
UCrowAttributes::UCrowAttributes()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentLife = 0;
	CurrentStamina = 0;
}


// Called when the game starts
void UCrowAttributes::BeginPlay()
{
	Super::BeginPlay();
	ModifyLife(StartingLife);
	if (StartWithFullStamina)
	{
		RestoreStamina(MaxStamina);
	}
}


// Called every frame
void UCrowAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RestoreStamina(DeltaTime*StaminaRecoverySpeed);
	// ...
}

void UCrowAttributes::DrainStamina(float Amount)
{
	if (CurrentStamina<=0 )
	{
		return;
	}
	CurrentStamina -= Amount;
	
	if (CurrentStamina <0)
	{
		CurrentStamina = 0;
	}
	OnStaminaChanged.Broadcast(CurrentStamina,GetStaminaPercent());
}

void UCrowAttributes::RestoreStamina(float Amount)
{
	if (CurrentStamina >= MaxStamina)
	{
		return;
	}
	CurrentStamina += Amount;
	
	if (CurrentStamina >MaxStamina)
	{
		CurrentStamina = MaxStamina;
	}
	
	OnStaminaChanged.Broadcast(CurrentStamina,GetStaminaPercent());
}

void UCrowAttributes::ModifyLife(int LifeToAdd)
{
	CurrentLife += LifeToAdd;
	if (CurrentLife<0 )
	{
		CurrentLife = 0;
		OnPlayerDied.Broadcast();
	}
	else if (CurrentLife>MaxLife)
	{
		CurrentLife = MaxLife;
	}
	OnLifeChanged.Broadcast(CurrentLife);
}

float UCrowAttributes::GetStaminaPercent()
{
	return CurrentStamina/MaxStamina;
}




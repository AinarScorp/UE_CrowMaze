// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CrowAttributes.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedSignature, float, NewStaminaAmount, float, StaminaPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLifeChangedSignature, int, NewLife);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDiedSignature);

UCLASS( ClassGroup=(Custom),Blueprintable,BlueprintType, meta=(BlueprintSpawnableComponent) )
class CROWMAZE_API UCrowAttributes : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCrowAttributes();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	void DrainStamina(float Amount);
	void RestoreStamina(float Amount);
	void ModifyLife(int LifeToAdd);
	float GetStaminaPercent();

public:
	UPROPERTY(BlueprintAssignable)
	FOnStaminaChangedSignature OnStaminaChanged;
	UPROPERTY(BlueprintAssignable)
	FOnLifeChangedSignature OnLifeChanged;
	UPROPERTY(BlueprintAssignable)
	FOnPlayerDiedSignature OnPlayerDied;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 MaxLife = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 StartingLife = 3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 CurrentLife;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxStamina = 100;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CurrentStamina = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool StartWithFullStamina = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float StaminaRecoverySpeed = 2;
};

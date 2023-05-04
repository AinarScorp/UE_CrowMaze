// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Crow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageTakenSignature);


class UInputMappingContext;
class UInputAction;
UCLASS()
class CROWMAZE_API ACrow : public APawn
{
	GENERATED_BODY()

public:
	ACrow();

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool IsGrounded();

private:
	void ExecuteDeath();
	void CreateComponents();
	void SetupEnhancedController() const;
	
	void SteerBird(const FInputActionValue& Value);
	
public:
	
	UPROPERTY(BlueprintAssignable)
	FOnDamageTakenSignature OnDamageTaken;
	
private:
#pragma region Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> SphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCrowAttributes> CrowAttributes;
#pragma endregion

#pragma region Inputs
	UPROPERTY(EditAnywhere)
	UInputMappingContext* BirdMappingContext;
	UPROPERTY(EditAnywhere)
	class UInputAction* MoveAction;
#pragma endregion


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bIsAlive = true;
};


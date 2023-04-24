// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Crow.generated.h"
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
private:
	UPROPERTY(EditAnywhere)
	UInputMappingContext* BirdMappingContext;
	UPROPERTY(EditAnywhere)
	class UInputAction* MoveAction;
	
	void SteerBird(const FInputActionValue& Value);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> SphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;


	//functions
	void CreateComponents();
	void SetupEnhancedController() const;


};

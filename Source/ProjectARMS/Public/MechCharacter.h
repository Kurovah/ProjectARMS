// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "MechCharacter.generated.h"

UCLASS(Abstract)
class PROJECTARMS_API AMechCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMechCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	bool grounded;

	UPROPERTY()
		class UAbilitySystemComponent* ASC;

	TArray<TSubclassOf<class UGameplayAbility>> mechAbilities;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void PossessedBy(AMechController* Controller);
	void Movement(const struct FInputActionValue& ActionValue);
	void JumpAction(const struct FInputActionValue& ActionValue);
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return ASC; };
	void GiveAbilities();
};

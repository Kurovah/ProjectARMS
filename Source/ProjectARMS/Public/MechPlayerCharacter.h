// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "MechAbility.h"
#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "MechPlayerCharacter.generated.h"

UCLASS(Abstract)
class PROJECTARMS_API AMechPlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMechPlayerCharacter();
	bool grounded;
	int facing = 0;

	UPROPERTY(EditDefaultsOnly)
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly)
		class USkeletalMeshComponent* LArmMesh;
	UPROPERTY(EditDefaultsOnly)
		class USkeletalMeshComponent* RArmMesh;
	UPROPERTY(EditDefaultsOnly)
		class USkeletalMeshComponent* LegsMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UAbilitySystemComponent* ASC;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TSubclassOf <UMechAbility> leftArmAbility;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TSubclassOf <UMechAbility> rightArmAbility;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TSubclassOf <UMechAbility> legsAbility;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		class UDataTable* armsTable;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		class UDataTable* coreTable;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		class UDataTable* legsTable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		class UMaterialInterface* parentMat;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* controller) override;
	void Movement(const struct FInputActionValue& ActionValue);
	void JumpAction(const struct FInputActionValue& ActionValue);
	void LeftArmAction(const struct FInputActionValue& ActionValue);
	void RightArmAction(const struct FInputActionValue& ActionValue);
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return ASC; };
	void GiveAbilities();
	void ConstructBody();
	void SetPeice(int type, int pieceindex);
};

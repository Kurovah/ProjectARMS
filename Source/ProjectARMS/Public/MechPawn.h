// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ArmStruct.h"
#include "LegStruct.h"
#include "BodyStruct.h"
#include "MechController.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MechPawn.generated.h"
#include <Runtime/Engine/Classes/Components/SphereComponent.h>

UCLASS()
class PROJECTARMS_API AMechPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMechPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//to contruct body
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* PlayerMesh;
	UPROPERTY(EditDefaultsOnly)
		USphereComponent* colliderSphere;

	//battleStats
	

	UPROPERTY(EditDefaultsOnly)
		float Health;
	UPROPERTY(EditDefaultsOnly)
		float moveSpeed;
	UPROPERTY(EditDefaultsOnly);
		float dashLength;

	//structs
	FArmStruct leftArmStruct;
	FArmStruct rightArmStruct;
	FLegStruct legStruct;
	FBodyStruct coreStruct;

	//misc
	FVector velocity;
	float gravity;
	bool isGrounded;
	float horizontalAxis;
	float jumpInput;

	

protected:
	//void GenerateBody();
	void Movement(const struct FInputActionValue& actionValue);
	void CheckGround();

};

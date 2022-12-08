// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MechPawn.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 LeftArm_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 RightArm_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Legs_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Body_id;

	//

	//battleStats
	UPROPERTY(EditDefaultsOnly)
		float Health;
	UPROPERTY(EditDefaultsOnly)
		float moveSpeed;
	UPROPERTY(EditDefaultsOnly);
		float dashLength;


};

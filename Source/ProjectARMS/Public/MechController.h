// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MechController.generated.h"
/**
 * 
 */
UCLASS()
class PROJECTARMS_API AMechController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void SetupInputComponent() override;

	UPROPERTY()
		class UInputMappingContext* mappingContext;
	UPROPERTY()
		class UInputAction* pawnInput;

};

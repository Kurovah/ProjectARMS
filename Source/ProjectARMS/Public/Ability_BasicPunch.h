// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MechAbility.h"
#include "GameFramework/Character.h"
#include "Ability_BasicPunch.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTARMS_API UAbility_BasicPunch : public UMechAbility
{
	GENERATED_BODY()

public:
		void ActivateAbility();
};

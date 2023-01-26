// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "ProjectArmsInstance.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTARMS_API UProjectArmsInstance : public UGameInstance
{
	GENERATED_BODY()
		
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CoreIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ArmLIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ArmRIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int LegIndex;
};
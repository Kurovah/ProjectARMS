// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttachmentData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTARMS_API FAttachmentData
{
	GENERATED_BODY()
public:
	TTuple<int, bool> coreData = TTuple<int,bool>(0,false);
	TTuple<int, bool> armLData = TTuple<int, bool>(0, false);
	TTuple<int, bool> armRData = TTuple<int, bool>(0, false);
	TTuple<int, bool> legData = TTuple<int, bool>(0, false);
};

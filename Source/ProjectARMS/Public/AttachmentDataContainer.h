// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "AttachmentData.h"
#include "AttachmentDataContainer.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct FAttachmentDataContainer : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = test)
		FAttachmentData data;

	FAttachmentDataContainer();
	~FAttachmentDataContainer();
};

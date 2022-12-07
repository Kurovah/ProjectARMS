// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "LegStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FLegStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString attachmentName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* attachmentMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* attachmentTexture;


};

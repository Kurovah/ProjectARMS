// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "BodyStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBodyStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString attachmentName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* attachmentMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* attachmentTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float hpValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float speedReduction;


};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FBodyAttachment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString attachmentName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool usingSkelMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* attachmentMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* attachmentMesh;

	FBodyAttachment();
	~FBodyAttachment();
};

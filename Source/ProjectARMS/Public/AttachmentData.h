// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttachmentData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAttachmentData
{
public:
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString attachmentName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool usingSkelMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* attachmentMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* attachmentSkelMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* attachmentMaterial;
	

	FAttachmentData();
	~FAttachmentData();
};

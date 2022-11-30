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
public:
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
		std::string attachmentName;
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* attachmentMesh;
	UPROPERTY(BlueprintReadWrite)
		UMaterial* attachmentMaterial;
	

	FAttachmentData();
	~FAttachmentData();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArmAttachments.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FArmAttachments
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString attachmentName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* attachmentMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* attachmentMaterial;
		

	FArmAttachments();
	~FArmAttachments();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "ArmStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FArmStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString attachmentName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* attachmentMeshL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* attachmentMeshR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* attachmentTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float damageValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float coolDownTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* projectile;
	


};

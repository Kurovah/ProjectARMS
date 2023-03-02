// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MechAbility.h"
#include "Engine/DataAsset.h"
#include "CoreAttachStruct.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct FCoreAttachStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name = "defaultName";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* texture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float healthValue;
};

USTRUCT(BlueprintType)
struct FArmAttachStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name = "defaultName";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* mirroredMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* texture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf < class UMechAbility> ability;
};

USTRUCT(BlueprintType)
struct FLegAttachStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name = "defaultName";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* texture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf <class UMechAbility> ability;
};

USTRUCT(BlueprintType)
struct FHitContext 
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector sourcePosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float damageValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float launchValue;
};

USTRUCT(BlueprintType)
struct FAttachmentUnlockStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAttachmentDataAsset* attachmentData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasBeenBought = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float attachmentCost = 10;
};

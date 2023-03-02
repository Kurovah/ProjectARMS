// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CoreAttachStruct.h"
#include "AttachmentDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTARMS_API UAttachmentDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name = "defaultName";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* texture;
};


UCLASS(BlueprintType)
class PROJECTARMS_API UCoreAttachmentDataAsset : public UAttachmentDataAsset
{
	GENERATED_BODY()
public:
};

UCLASS(BlueprintType)
class PROJECTARMS_API UArmAttachmentDataAsset : public UAttachmentDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* mirroredMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf < class UMechAbility> ability;
};

UCLASS(BlueprintType)
class PROJECTARMS_API ULegAttachmentDataAsset : public UAttachmentDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf <class UMechAbility> ability;
};

UCLASS(BlueprintType)
class PROJECTARMS_API UAttachmentUnlockDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<struct FAttachmentUnlockStruct> coreData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<struct FAttachmentUnlockStruct> armData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<struct FAttachmentUnlockStruct> legData;

};

UCLASS(BlueprintType)
class PROJECTARMS_API UAttachConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCoreAttachmentDataAsset* core;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UArmAttachmentDataAsset* armL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UArmAttachmentDataAsset* armR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ULegAttachmentDataAsset* legs;

};

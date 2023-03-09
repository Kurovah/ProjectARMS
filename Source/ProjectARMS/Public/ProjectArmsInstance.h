// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "AttachmentDataAsset.h"
#include "ProjectArmsInstance.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTARMS_API UProjectArmsInstance : public UGameInstance
{
	GENERATED_BODY()
		
public:
	UProjectArmsInstance();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CoreIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ArmLIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ArmRIndex = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int LegIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float currency = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAttachConfig* attachmentConfiguration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAttachmentUnlockDataAsset* unlockData;
	UFUNCTION(BlueprintCallable, Category = "GameInstance functions")
		void AddCurrency(UPARAM() float amount);
};

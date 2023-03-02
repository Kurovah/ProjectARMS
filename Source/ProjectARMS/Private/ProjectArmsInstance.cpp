// Fill out your copyright notice in the Description page of Project Settings.

#include "UObject/ConstructorHelpers.h"
#include "ProjectArmsInstance.h"

UProjectArmsInstance::UProjectArmsInstance()
{
	static ConstructorHelpers::FObjectFinder <UAttachmentUnlockDataAsset> AUDA(TEXT("/Script/ProjectARMS.AttachmentUnlockDataAsset'/Game/Game_Data/UnlockData.UnlockData'"));
	if (AUDA.Succeeded()) {
		unlockData = AUDA.Object;
	}
	

	static ConstructorHelpers::FObjectFinder <UAttachConfig> AC(TEXT("/Script/ProjectARMS.AttachConfig'/Game/Game_Data/AttachConfig.AttachConfig'"));
	if (AC.Succeeded()) {
		attachmentConfiguration = AC.Object;
	}
}

void UProjectArmsInstance::AddCurrency(UPARAM(ref) float amount)
{
	currency += amount;
}

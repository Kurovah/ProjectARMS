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

	static ConstructorHelpers::FObjectFinder <UDataTable> DT(TEXT("/Script/Engine.DataTable'/Game/Game_Data/UnlockDataTable.UnlockDataTable'"));
	if (DT.Succeeded()) {
		unlockDataTable = DT.Object;
	}

	///Script/Engine.DataTable'/Game/Game_Data/UnlockDataTable.UnlockDataTable'
}

void UProjectArmsInstance::AddCurrency(UPARAM(ref) float amount)
{
	currency += amount;
}

void UProjectArmsInstance::Winstage()
{
	WinStageDelegate.Broadcast();
}

bool UProjectArmsInstance::GetAttachmentUnlocked(UPARAM()FString attachmentName)
{
	auto list = unlockDataTable->GetRowNames();
	//go through the list for a name, if name found then unlock it
	for (auto i : list) {
		FAttachmentUnlockStruct* a = unlockDataTable->FindRow<FAttachmentUnlockStruct>(i, "");
		if (a->attachmentData->name == attachmentName)
			return a->hasBeenBought;
	}
	return false;
}

void UProjectArmsInstance::UnlockAttachement(UPARAM() FString attachmentName)
{
	//cast to datatable
	auto list = unlockDataTable->GetRowNames();
	//go through the list for a name, if name found then unlock it
	for (auto i : list) {
		FAttachmentUnlockStruct* a = unlockDataTable->FindRow<FAttachmentUnlockStruct>(i,"");
		if (a->attachmentData->name == attachmentName)
			a->hasBeenBought = true;
	}
}

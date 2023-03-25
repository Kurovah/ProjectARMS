// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentDataAsset.h"

void UAttachmentUnlockDataAsset::UnlockAttachment(int listIndex, int index)
{
	TArray<struct FAttachmentUnlockStruct> list;
	switch (listIndex) {
	case 0:
		list = coreData;
		break;
	case 1:
		list = armData;
		break;
	case 2:
		list = legData;
		break;
	}

	index = FMath::Clamp(index, 0, list.Num());
	list[index].hasBeenBought = true;
}

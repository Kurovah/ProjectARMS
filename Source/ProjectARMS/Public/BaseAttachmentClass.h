// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECTARMS_API BaseAttachmentClass
{
public:
	BaseAttachmentClass(USkeletalMesh* _mesh, UTexture2D* _tex);
	~BaseAttachmentClass();
	UPROPERTY()
		USkeletalMesh* partMesh;
	UPROPERTY()
		UTexture2D* partTexture;
};

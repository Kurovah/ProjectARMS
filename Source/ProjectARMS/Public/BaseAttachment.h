// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAttachment.generated.h"

UCLASS()
class PROJECTARMS_API ABaseAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	
	// Sets default values for this actor's properties
	ABaseAttachment();
	UPROPERTY(EditAnywhere)
		int32 attachmentId;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* attachmentMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};

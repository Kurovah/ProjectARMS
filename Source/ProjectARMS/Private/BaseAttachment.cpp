// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttachment.h"

// Sets default values
ABaseAttachment::ABaseAttachment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ABaseAttachment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseAttachment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


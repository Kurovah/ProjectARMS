// Fill out your copyright notice in the Description page of Project Settings.


#include "MechPawn.h"

// Sets default values
AMechPawn::AMechPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = PlayerMesh;

}

// Called when the game starts or when spawned
void AMechPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMechPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMechPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "MechPawn.h"

// Sets default values
AMechPawn::AMechPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

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
	FVector location = GetActorLocation();
	location += velocity * DeltaTime;
	SetActorLocation(location);
	
}

// Called to bind functionality to input
void AMechPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis(TEXT("HorizontalMapping"), this , &AMechPawn::HorizontalMovement);
	InputComponent->BindAxis(TEXT("VerticalMapping"), this , &AMechPawn::VerticalMovement);

}

void AMechPawn::HorizontalMovement(float AxisVal) 
{
	velocity.Y = AxisVal * 100.0f;
}
void AMechPawn::VerticalMovement(float AxisVal)
{

}
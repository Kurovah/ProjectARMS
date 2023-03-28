// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MechPlayerCharacter.h"

// Sets default values
ALevelCamera::ALevelCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	SpringArmComp->bDoCollisionTest = false;

}

// Called when the game starts or when spawned
void ALevelCamera::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	playerActor = OurPlayerController->GetCharacter();
	//Smoothly transition to our actor on begin play.
	OurPlayerController->SetViewTargetWithBlend((AActor*)this, 0.0f);
	SetActorLocation(playerActor->GetActorLocation() + Offset);

}

// Called every frame
void ALevelCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto pPos = playerActor->GetActorLocation();
	auto player = (AMechPlayerCharacter*)playerActor;

	Offset.Y = 100 * player->facing;

	SetActorLocation(FMath::Lerp(GetActorLocation(), pPos + Offset, smoothing));
}


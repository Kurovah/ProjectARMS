// Fill out your copyright notice in the Description page of Project Settings.


#include "MechPawn.h"
#include "MechController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


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

	//

	//gravity
	velocity.Z -= 0.1f;
	FVector location = GetActorLocation();
	location += velocity;
	SetActorLocation(location);
}

// Called to bind functionality to input
void AMechPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	AMechController* FPC = Cast<AMechController>(Controller);
	check(EIC && FPC);
	EIC->BindAction(FPC->pawnInput, ETriggerEvent::Triggered, this, &AMechPawn::Movement);

	ULocalPlayer* LocalPlayer = FPC->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(FPC->mappingContext, 0);

}

void AMechPawn::Movement(const struct FInputActionValue& actionValue) 
{
	FVector2D Input = actionValue.Get<FInputActionValue::Axis2D>();

	if (Input.Y > 0)
		velocity.Z = 10;

	
	velocity.Y = Input.X;


	FVector location = GetActorLocation();
	location += velocity;
	SetActorLocation(location);
}

void AMechPawn::CheckGround()
{
	FHitResult OutHit;
	FVector DownVec = -RootComponent->GetUpVector();

}

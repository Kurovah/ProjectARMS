// Fill out your copyright notice in the Description page of Project Settings.


#include "MechPlayerCharacter.h"
#include "MechController.h"
#include "CoreAttachStruct.h"

#include "ProjectArmsInstance.h"
#include "GameplayAbilities/Public/Abilities/GameplayAbility.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/Class.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
AMechPlayerCharacter::AMechPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("AimArm"));
	LArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LArm"));
	RArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RArm"));
	LegsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs"));

	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->TargetArmLength = 20;

	LArmMesh->SetupAttachment(GetMesh());
	RArmMesh->SetupAttachment(GetMesh());
	LegsMesh->SetupAttachment(GetMesh());

	GetMesh()->SetLeaderPoseComponent(GetMesh());
}

// Called when the game starts or when spawned
void AMechPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	ConstructBody();
	GiveAbilities();
}

// Called every frame
void AMechPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMechPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	AMechController* FPC = Cast<AMechController>(Controller);
	check(EIC && FPC);
	EIC->BindAction(FPC->pawnInput, ETriggerEvent::Triggered, this, &AMechPlayerCharacter::Movement);
	EIC->BindAction(FPC->pawnjumpInput, ETriggerEvent::Started, this, &AMechPlayerCharacter::JumpAction);
	EIC->BindAction(FPC->pawnLArmInput, ETriggerEvent::Started, this, &AMechPlayerCharacter::LeftArmAction);

	ULocalPlayer* LocalPlayer = FPC->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(FPC->mappingContext, 0);
}

void AMechPlayerCharacter::PossessedBy(AController* controller)
{
	Super::PossessedBy(controller);
	ASC->InitAbilityActorInfo(this, this);
}

void AMechPlayerCharacter::Movement(const FInputActionValue& ActionValue)
{
	FVector2D Input = ActionValue.Get<FInputActionValue::Axis2D>();
	AddMovementInput(FVector::RightVector * Input.X, 2.0f, true);
}

void AMechPlayerCharacter::JumpAction(const FInputActionValue& ActionValue)
{
	auto MovementComponent = GetCharacterMovement();
	if (!MovementComponent->IsFalling())
	{
		LaunchCharacter(FVector::UpVector * 500.0f, false, true);
	}

}

void AMechPlayerCharacter::LeftArmAction(const FInputActionValue& ActionValue)
{
	ASC->TryActivateAbilityByClass(leftArmAbility);
}

void AMechPlayerCharacter::RightArmAction(const FInputActionValue& ActionValue)
{
}

void AMechPlayerCharacter::GiveAbilities()
{
	//giving abilities
	//ASC->GiveAbility(FGameplayAbilitySpec(leftArmAbility, leftArmAbility.GetDefaultObject()->GetAbilityLevel()));
}

void AMechPlayerCharacter::ConstructBody()
{
	int armRIndex, armLIndex, legsIndex, coreIndex;
	UProjectArmsInstance* GI = Cast<UProjectArmsInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		// Do Something
		armLIndex = GI->ArmLIndex;
		armRIndex = GI->ArmRIndex;
		coreIndex = GI->CoreIndex;
		legsIndex = GI->LegIndex;


		TArray<FName> tableRows = armsTable->GetRowNames();
		auto rowName = tableRows[armLIndex];
		auto rowData = armsTable->FindRow<FArmAttachStruct>(rowName, "");
		auto mesh = rowData->mesh;

		LArmMesh->SetSkeletalMesh(mesh);
	}
}


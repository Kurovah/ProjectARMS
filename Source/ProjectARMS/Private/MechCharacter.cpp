// Fill out your copyright notice in the Description page of Project Settings.


#include "MechCharacter.h"
#include "MechController.h"
#include "CoreAttachStruct.h"


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
#include <ProjectARMS/Public/ProjectArmsInstance.h>


// Sets default values
AMechCharacter::AMechCharacter()
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
	//ASC->InitAbilityActorInfo(this, this);

	/*static ConstructorHelpers::FObjectFinder<UDataTable> armTableObj(TEXT("DataTable'/Game/Datatables/Arms.Arms'"));
	if (armTableObj.Succeeded())
	{
		armsTable = armTableObj.Object;
	}*/
}

// Called when the game starts or when spawned
void AMechCharacter::BeginPlay()
{
	Super::BeginPlay();
	ConstructBody();
	GiveAbilities();
}

// Called every frame
void AMechCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMechCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	AMechController* FPC = Cast<AMechController>(Controller);
	check(EIC && FPC);
	EIC->BindAction(FPC->pawnInput, ETriggerEvent::Triggered, this, &AMechCharacter::Movement);
	EIC->BindAction(FPC->pawnjumpInput, ETriggerEvent::Started, this, &AMechCharacter::JumpAction);
	EIC->BindAction(FPC->pawnLArmInput, ETriggerEvent::Started, this, &AMechCharacter::LeftArmAction);

	ULocalPlayer* LocalPlayer = FPC->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(FPC->mappingContext, 0);

}

void AMechCharacter::PossessedBy(AController* controller)
{
	Super::PossessedBy(controller);
	ASC->InitAbilityActorInfo(this, this);
}

void AMechCharacter::Movement(const FInputActionValue& ActionValue)
{
	FVector2D Input = ActionValue.Get<FInputActionValue::Axis2D>();
	AddMovementInput(FVector::RightVector * Input.X, 2.0f, true);
}

void AMechCharacter::JumpAction(const FInputActionValue& ActionValue)
{
	auto MovementComponent = GetCharacterMovement();
	if (!MovementComponent->IsFalling()) 
	{
		LaunchCharacter(FVector::UpVector * 500.0f, false, true);
	}
	
}

void AMechCharacter::LeftArmAction(const FInputActionValue& ActionValue)
{
	ASC->TryActivateAbilityByClass(leftArmAbility);
}

void AMechCharacter::RightArmAction(const FInputActionValue& ActionValue)
{
}

void AMechCharacter::GiveAbilities()
{
	//giving abilities
	for (TSubclassOf<UMechAbility>& ability: mechAbilities) {
		ASC->GiveAbility(FGameplayAbilitySpec(ability, ability.GetDefaultObject()->GetAbilityLevel()));
	}

	ASC->GiveAbility(FGameplayAbilitySpec(leftArmAbility, leftArmAbility.GetDefaultObject()->GetAbilityLevel()));
}

void AMechCharacter::ConstructBody()
{
	//UProjectArmsInstance* gi = Cast<UProjectArmsInstance>(GetGameInstance());

	/*UDataTable* legsTable;
	UDataTable* coresTable;*/

	/*auto armMeshes = armsTable->GetRowNames();
	auto meshName = armMeshes[0];
	auto armStruct = armsTable->FindRow<FArmAttachStruct>(meshName, "");

	LArmMesh->SetSkeletalMesh(armStruct->mesh);*/
}


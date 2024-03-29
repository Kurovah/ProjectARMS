// Fill out your copyright notice in the Description page of Project Settings.


#include "MechPlayerCharacter.h"
#include "MechController.h"
#include "CoreAttachStruct.h"
#include "AttachmentDataAsset.h"

#include "ProjectArmsInstance.h"
#include "GameplayAbilities/Public/Abilities/GameplayAbility.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/Class.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <MathUtil.h>


// Sets default values
AMechPlayerCharacter::AMechPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	LArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LArm"));
	RArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RArm"));
	LegsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs"));

	LArmMesh->SetupAttachment(GetMesh());
	RArmMesh->SetupAttachment(GetMesh());
	LegsMesh->SetupAttachment(GetMesh());
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
	FRotator r = GetActorRotation();
	if (facing == 1) {
		r.Yaw = 0;
	}
	else {
		r.Yaw = 180;
	}
	SetActorRotation(r);

	if (armBlend > 0) {
		armBlend -= .1f;
	}
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
	EIC->BindAction(FPC->pawnRArmInput, ETriggerEvent::Started, this, &AMechPlayerCharacter::RightArmAction);

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
	if (canAct) {
		AddMovementInput(FVector::RightVector * Input.X, 2.0f, true);
		if (Input.X != 0) {
			facing = Input.X;
		}
	}
	
}

void AMechPlayerCharacter::JumpAction(const FInputActionValue& ActionValue)
{
	auto MovementComponent = GetCharacterMovement();
	if (!MovementComponent->IsFalling())
	{
		LaunchCharacter(FVector::UpVector * 500.0f, false, true);
	}
	else {
		ASC->TryActivateAbilityByClass(legsAbility);
	}

}

void AMechPlayerCharacter::LeftArmAction(const FInputActionValue& ActionValue)
{
	if (canAct) {
		GetCharacterMovement()->Velocity.Set(0, 0, 0);
		abilitySide = -1;
		ASC->TryActivateAbilityByClass(leftArmAbility);
	}
	
}

void AMechPlayerCharacter::RightArmAction(const FInputActionValue& ActionValue)
{
	if (canAct) {
		GetCharacterMovement()->Velocity.Set(0, 0, 0);
		abilitySide = 1;
		ASC->TryActivateAbilityByClass(rightArmAbility);
	}
	
}

void AMechPlayerCharacter::GiveAbilities()
{
	//giving abilities
	if (leftArmAbility != NULL)
	{
		ASC->GiveAbility(FGameplayAbilitySpec(leftArmAbility, leftArmAbility.GetDefaultObject()->GetAbilityLevel()));
	}
	if (rightArmAbility != NULL)
	{
		ASC->GiveAbility(FGameplayAbilitySpec(rightArmAbility, rightArmAbility.GetDefaultObject()->GetAbilityLevel()));
	}
	if (legsAbility != NULL)
	{
		ASC->GiveAbility(FGameplayAbilitySpec(legsAbility, legsAbility.GetDefaultObject()->GetAbilityLevel()));
	}
	
}

void AMechPlayerCharacter::ConstructBody()
{
	UProjectArmsInstance* GI = Cast<UProjectArmsInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		//// Do Something
		//armLIndex = GI->ArmLIndex;
		//armRIndex = GI->ArmRIndex;
		//coreIndex = GI->CoreIndex;
		//legsIndex = GI->LegIndex;

		////set the peices
		//SetPeice(0, coreIndex);
		//SetPeice(1, armLIndex);
		//SetPeice(2, armRIndex);
		//SetPeice(3, legsIndex);

		auto Data = GI->attachmentConfiguration;
		SetPieceNew(0, Data->core);
		SetPieceNew(1, Data->armL);
		SetPieceNew(2, Data->armR);
		SetPieceNew(3, Data->legs);

	}
}

void AMechPlayerCharacter::SetPeice(int type, int pieceindex)
{
	USkeletalMeshComponent* skelmeshtoChange = NULL;
	TSubclassOf <UMechAbility> abilityToSet;


	TArray<FName> tableRows;

	//data from rows
	UTexture2D* peiceTex = NULL;
	USkeletalMesh* peiceMesh = NULL;
	TSubclassOf <UMechAbility> pieceAbility;
	FName rowName;
	//material
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(parentMat, this);
	

	switch (type) {
	case 0://core
		skelmeshtoChange = GetMesh();
		tableRows = coreTable->GetRowNames();
		rowName = tableRows[pieceindex];

		peiceTex = coreTable->FindRow<FCoreAttachStruct>(rowName, "")->texture;
		peiceMesh = coreTable->FindRow<FCoreAttachStruct>(rowName, "")->mesh;
		maxHealth = health = coreTable->FindRow<FCoreAttachStruct>(rowName, "")->healthValue;
		break;

	case 1://arms//L
	case 2://R
		skelmeshtoChange = type == 1 ? LArmMesh : RArmMesh;
		
		tableRows = armsTable->GetRowNames();
		rowName = tableRows[pieceindex];

		peiceTex = armsTable->FindRow<FArmAttachStruct>(rowName, "")->texture;
		peiceMesh = type == 1 ? armsTable->FindRow<FArmAttachStruct>(rowName, "")->mesh : 
			armsTable->FindRow<FArmAttachStruct>(rowName, "")->mirroredMesh;

		if (type == 1) { leftArmAbility = armsTable->FindRow<FArmAttachStruct>(rowName, "")->ability; } else { rightArmAbility = armsTable->FindRow<FArmAttachStruct>(rowName, "")->ability; }
		break;

	case 3://legs
		skelmeshtoChange = LegsMesh;
		tableRows = legsTable->GetRowNames();
		rowName = tableRows[pieceindex];

		peiceTex = legsTable->FindRow<FLegAttachStruct>(rowName, "")->texture;
		peiceMesh = legsTable->FindRow<FLegAttachStruct>(rowName, "")->mesh;
		legsAbility = legsTable->FindRow<FLegAttachStruct>(rowName, "")->ability;
		break;
	}

	//setting peice
	if (peiceMesh != NULL) {
		skelmeshtoChange->SetSkeletalMesh(peiceMesh);
		DynMaterial->SetTextureParameterValue("BaseTex", peiceTex);
		skelmeshtoChange->SetMaterial(0, DynMaterial);
	}
}

void AMechPlayerCharacter::SetPieceNew(int type, class UAttachmentDataAsset* attachmentConfig)
{
	USkeletalMeshComponent* meshToChange = NULL;
	USkeletalMesh* mesh = NULL;

	UTexture2D* peiceTex = NULL;
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(parentMat, this);

	UCoreAttachmentDataAsset* cData = NULL;
	UArmAttachmentDataAsset* aLData = NULL;
	UArmAttachmentDataAsset* aRData = NULL;
	ULegAttachmentDataAsset* lData = NULL;

	switch (type) {
	case 0://core
		meshToChange = GetMesh();
		cData = (UCoreAttachmentDataAsset*)attachmentConfig;
		mesh = cData->mesh;
		peiceTex = cData->texture;
		break;

	case 1://armL
		meshToChange = LArmMesh;
		aLData = (UArmAttachmentDataAsset*)attachmentConfig;
		mesh = aLData->mesh;
		peiceTex = aLData->texture;
		leftArmAbility = aLData->ability;
		break;

	case 2://armR
		meshToChange = RArmMesh;
		aRData = (UArmAttachmentDataAsset*)attachmentConfig;
		mesh = aRData->mirroredMesh;
		peiceTex = aRData->texture;
		rightArmAbility = aRData->ability;
		break;

	case 3://legs
		meshToChange = LegsMesh;
		lData = (ULegAttachmentDataAsset*)attachmentConfig;
		mesh = lData->mesh;
		peiceTex = lData->texture;
		legsAbility = lData->ability;
		break;
	}

	if (mesh != NULL) {
		meshToChange->SetSkeletalMesh(mesh);
		DynMaterial->SetTextureParameterValue("BaseTex", peiceTex);
		meshToChange->SetMaterial(0, DynMaterial);
	}
	
}

void AMechPlayerCharacter::KillCharacter()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), deathParticles, GetActorLocation());
	KillDelegate.Broadcast();
}

void AMechPlayerCharacter::ApplyHit(UPARAM(ref) FHitContext hitcontext)
{
	FVector place = GetActorLocation();
	FVector hitDir = place - hitcontext.sourcePosition;
	hitDir.X = 0;
	hitDir.Z = hitcontext.launchValue / 2;
	facing = hitDir.Y > 0 ? -1 : 1;
	health -= 1;
	LaunchCharacter(hitDir.GetSafeNormal() * 1000, true, true);
	
	if (health <= 0)
		KillCharacter();

}




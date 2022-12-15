// Fill out your copyright notice in the Description page of Project Settings.


#include "MechController.h"
#include "InputAction.h"
#include "InputMappingContext.h"



void AMechController::SetupInputComponent() {
	Super::SetupInputComponent();

	mappingContext = NewObject<UInputMappingContext>(this);

	inputAction = NewObject<UInputAction>(this);
	inputAction->ValueType = EInputActionValueType::Axis2D;
	mappingContext->MapKey(inputAction, EKeys::W);
}

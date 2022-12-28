// Fill out your copyright notice in the Description page of Project Settings.


#include "MechController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"

static void MapKey(UInputMappingContext* _context, UInputAction* _action, FKey _Key, bool bNegate = false, bool bSwizzle= false, EInputAxisSwizzle _swizzle = EInputAxisSwizzle::YXZ) 
{
	FEnhancedActionKeyMapping& Mapping = _context->MapKey(_action, _Key);
	UObject* Outer = _context->GetOuter();

	if (bNegate) {
		UInputModifierNegate* Negate = NewObject<UInputModifierNegate>(Outer);
		Mapping.Modifiers.Add(Negate);
	}

	if (bSwizzle) {
		UInputModifierSwizzleAxis* Swizzle = NewObject<UInputModifierSwizzleAxis>(Outer);
		Swizzle->Order = _swizzle;
		Mapping.Modifiers.Add(Swizzle);
	}
}

void AMechController::SetupInputComponent() {
	Super::SetupInputComponent();

	mappingContext = NewObject<UInputMappingContext>(this);

	pawnInput = NewObject<UInputAction>(this);
	pawnInput->ValueType = EInputActionValueType::Axis2D;

	//mapping
	MapKey(mappingContext, pawnInput, EKeys::D, true, false);
	MapKey(mappingContext, pawnInput, EKeys::A, false, false);
	MapKey(mappingContext, pawnInput, EKeys::W, false, true);
	MapKey(mappingContext, pawnInput, EKeys::S, true, true);
}

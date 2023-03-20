// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectARMSGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

AProjectARMSGameModeBase::AProjectARMSGameModeBase()
{
	//static ConstructorHelpers::FClassFinder<ACharacter>  MechClass(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/MechPlayerCharacterBP.MechPlayerCharacterBP'"));
	/*static ConstructorHelpers::FClassFinder<ACharacter>  MechClass(TEXT("/Game/BluePrints/MechPlayerCharacterBP"));
	if (MechClass.Succeeded()) {
		DefaultPawnClass = MechClass.Class;
	}*/
	
}

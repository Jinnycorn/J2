// Copyright Epic Games, Inc. All Rights Reserved.


#include "J2GameModeBase.h"

void AJ2GameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("HELLO"));
	}
}
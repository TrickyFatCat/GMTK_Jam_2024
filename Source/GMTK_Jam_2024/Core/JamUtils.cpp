// Fill out your copyright notice in the Description page of Project Settings.


#include "JamUtils.h"

#include "JamCoreGameMode.h"
#include "Kismet/GameplayStatics.h"

AScales* UJamUtils::GetRegisteredScales(const UObject* WorldContextObj)
{
	const AJamCoreGameMode* GameMode = GetCoreGameMode(WorldContextObj);

	if (!IsValid(GameMode))
	{
		return nullptr;
	}

	return GameMode->GetScales();
}

AJamCoreGameMode* UJamUtils::GetCoreGameMode(const UObject* WorldContextObj)
{
	return Cast<AJamCoreGameMode>(UGameplayStatics::GetGameMode(WorldContextObj));
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "JamCoreGameMode.h"

#include "GMTK_Jam_2024/Actors/Scales.h"

void AJamCoreGameMode::RegisterScales(AScales* NewScales)
{
	if (!IsValid(NewScales))
	{
		return;
	}

	Scales = NewScales;
}

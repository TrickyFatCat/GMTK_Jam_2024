// Fill out your copyright notice in the Description page of Project Settings.


#include "Scales.h"

#include "Entity.h"
#include "Bowl.h"
#include "GMTK_Jam_2024/Components/EntityManagerComponent.h"
#include "GMTK_Jam_2024/Components/WeightComponent.h"
#include "GMTK_Jam_2024/Core/JamCoreGameMode.h"
#include "GMTK_Jam_2024/Core/JamUtils.h"


AScales::AScales()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AScales::BeginPlay()
{
	if (IsValid(RightBowl))
	{
		RightBowl->GetWeightComponent()->OnWeightAdded.AddUniqueDynamic(this, &AScales::HandleWeightAdded);
		RightBowl->GetWeightComponent()->OnWeightRemoved.AddUniqueDynamic(this, &AScales::HandleWeightRemoved);
	}

	if (IsValid(LeftBowl))
	{
		LeftBowl->GetWeightComponent()->OnWeightAdded.AddUniqueDynamic(this, &AScales::HandleWeightAdded);
		LeftBowl->GetWeightComponent()->OnWeightRemoved.AddUniqueDynamic(this, &AScales::HandleWeightRemoved);
	}

	AJamCoreGameMode* GameMode = UJamUtils::GetCoreGameMode(this);

	if (IsValid(GameMode))
	{
		GameMode->RegisterScales(this);
	}
	
	Super::BeginPlay();
}

bool AScales::AddEntity(AEntity* Entity)
{
	if (!IsValid(Entity) || !IsValid(RightBowl))
	{
		return false;
	}

	return RightBowl->AddEntity(Entity);
}

bool AScales::RemoveEntity(AEntity* Entity)
{
	if (!IsValid(Entity) || !IsValid(RightBowl))
	{
		return false;
	}

	return RightBowl->RemoveEntity(Entity);
}

bool AScales::AddTargetEntity(AEntity* Entity)
{
	if (!IsValid(Entity) || !IsValid(LeftBowl))
	{
		return false;
	}

	return LeftBowl->AddEntity(Entity);
}

bool AScales::RemoveTargetEntity(AEntity* Entity)
{
	if (!IsValid(Entity) || !IsValid(LeftBowl))
	{
		return false;
	}

	return LeftBowl->RemoveEntity(Entity);
}

void AScales::CalculateBalance()
{
	if (!IsValid(RightBowl) || !IsValid(LeftBowl))
	{
		return;
	}

	const float RightBowlWeight = static_cast<float>(RightBowl->GetWeight());
	const float LeftBowlWeight = static_cast<float>(LeftBowl->GetWeight());
	WeightBalance = RightBowlWeight / LeftBowlWeight - 1.f;
}

void AScales::HandleWeightAdded(UWeightComponent* WeightComponent,
                                const int32 NewWeight,
                                const int32 DeltaWeight)
{
	CalculateBalance();
}

void AScales::HandleWeightRemoved(UWeightComponent* WeightComponent,
                                  const int32 NewWeight,
                                  const int32 DeltaWeight)
{
	CalculateBalance();
}

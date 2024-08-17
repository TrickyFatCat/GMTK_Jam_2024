// Fill out your copyright notice in the Description page of Project Settings.


#include "Scales.h"

#include "Entity.h"
#include "Bowl.h"
#include "GMTK_Jam_2024/Components/EntityManagerComponent.h"
#include "GMTK_Jam_2024/Components/WeightComponent.h"


AScales::AScales()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AScales::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(RightBowl))
	{
		RightBowl->GetWeightComponent()->OnWeightAdded.AddUniqueDynamic(this, &AScales::HandleWeightAdded);
		RightBowl->GetWeightComponent()->OnWeightRemoved.AddUniqueDynamic(this, &AScales::HandleWeightRemoved);
	}
}

bool AScales::AddEntity(AEntity* Entity) const
{
	if (!IsValid(Entity) || !IsValid(RightBowl))
	{
		return false;
	}

	return RightBowl->AddEntity(Entity);
}

bool AScales::RemoveEntity(AEntity* Entity) const
{
	if (!IsValid(Entity) || !IsValid(RightBowl))
	{
		return false;
	}

	return RightBowl->RemoveEntity(Entity);
}

void AScales::CalculateBalance()
{
	if (!IsValid(RightBowl) || !IsValid(LeftScaleBowl))
	{
		return;
	}
	
	const float RightBowlWeight = static_cast<float>(RightBowl->GetWeight());
	const float LeftBowlWeight = static_cast<float>(LeftScaleBowl->GetWeight());
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

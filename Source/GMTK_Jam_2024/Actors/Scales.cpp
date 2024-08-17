// Fill out your copyright notice in the Description page of Project Settings.


#include "Scales.h"

#include "EntityBase.h"
#include "ScaleBowl.h"
#include "GMTK_Jam_2024/Components/EntityManagerComponent.h"
#include "GMTK_Jam_2024/Components/WeightComponent.h"


AScales::AScales()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AScales::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(RightScaleBowl))
	{
		RightScaleBowl->GetWeightComponent()->OnWeightAdded.AddUniqueDynamic(this, &AScales::HandleWeightAdded);
		RightScaleBowl->GetWeightComponent()->OnWeightRemoved.AddUniqueDynamic(this, &AScales::HandleWeightRemoved);
	}
}

bool AScales::AddEntity(AEntityBase* Entity) const
{
	if (!IsValid(Entity) || !IsValid(RightScaleBowl))
	{
		return false;
	}

	return RightScaleBowl->AddEntity(Entity);
}

bool AScales::RemoveEntity(AEntityBase* Entity) const
{
	if (!IsValid(Entity) || !IsValid(RightScaleBowl))
	{
		return false;
	}

	return RightScaleBowl->RemoveEntity(Entity);
}

void AScales::CalculateBalance()
{
	if (!IsValid(RightScaleBowl) || !IsValid(LeftScaleBowl))
	{
		return;
	}
	
	const float RightBowlWeight = static_cast<float>(RightScaleBowl->GetWeight());
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

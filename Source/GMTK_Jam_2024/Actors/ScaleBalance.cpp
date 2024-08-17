// Fill out your copyright notice in the Description page of Project Settings.


#include "ScaleBalance.h"

#include "EntityBase.h"
#include "ScaleBowl.h"
#include "GMTK_Jam_2024/Components/EntityManagerComponent.h"
#include "GMTK_Jam_2024/Components/WeightComponent.h"


AScaleBalance::AScaleBalance()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AScaleBalance::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(RightScaleBowl))
	{
		RightScaleBowl->GetWeightComponent()->OnWeightAdded.AddUniqueDynamic(this, &AScaleBalance::HandleWeightAdded);
		RightScaleBowl->GetWeightComponent()->OnWeightRemoved.AddUniqueDynamic(this, &AScaleBalance::HandleWeightRemoved);
	}
}

bool AScaleBalance::AddEntity(AEntityBase* Entity) const
{
	if (!IsValid(Entity) || !IsValid(RightScaleBowl))
	{
		return false;
	}

	return RightScaleBowl->AddEntity(Entity);
}

bool AScaleBalance::RemoveEntity(AEntityBase* Entity) const
{
	if (!IsValid(Entity) || !IsValid(RightScaleBowl))
	{
		return false;
	}

	return RightScaleBowl->RemoveEntity(Entity);
}

void AScaleBalance::CalculateBalance()
{
	if (!IsValid(RightScaleBowl) || !IsValid(LeftScaleBowl))
	{
		return;
	}
	
	const float RightBowlWeight = static_cast<float>(RightScaleBowl->GetWeight());
	const float LeftBowlWeight = static_cast<float>(LeftScaleBowl->GetWeight());
	WeightBalance = RightBowlWeight / LeftBowlWeight - 1.f;
}

void AScaleBalance::HandleWeightAdded(UWeightComponent* WeightComponent,
                                      const int32 NewWeight,
                                      const int32 DeltaWeight)
{
	CalculateBalance();
}

void AScaleBalance::HandleWeightRemoved(UWeightComponent* WeightComponent,
                                        const int32 NewWeight,
                                        const int32 DeltaWeight)
{
	CalculateBalance();
}

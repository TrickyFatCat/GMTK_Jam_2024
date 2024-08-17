// Fill out your copyright notice in the Description page of Project Settings.


#include "ScaleBalance.h"

#include "EntityBase.h"
#include "ScaleBowl.h"


AScaleBalance::AScaleBalance()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AScaleBalance::BeginPlay()
{
	Super::BeginPlay();
	
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

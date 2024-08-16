// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityBase.h"

#include "Components/BoxComponent.h"
#include "GMTK_Jam_2024/Components/WeightComponent.h"


AEntityBase::AEntityBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>(FName("Collision"));
	SetRootComponent(Collision);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	WeightComponent = CreateDefaultSubobject<UWeightComponent>(FName("Weight"));
}

int32 AEntityBase::GetCurrentWeight() const
{
	if (!IsValid(WeightComponent))
	{
		return -1;
	}

	return WeightComponent->GetCurrentWeight();
}

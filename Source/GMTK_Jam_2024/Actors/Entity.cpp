// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"

#include "Components/BoxComponent.h"
#include "GMTK_Jam_2024/Components/WeightComponent.h"


AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>(FName("Collision"));
	SetRootComponent(Collision);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	WeightComponent = CreateDefaultSubobject<UWeightComponent>(FName("Weight"));
}

int32 AEntity::GetCurrentWeight() const
{
	if (!IsValid(WeightComponent))
	{
		return -1;
	}

	return WeightComponent->GetCurrentWeight();
}

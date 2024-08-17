// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"

#include "Components/BoxComponent.h"
#include "GMTK_Jam_2024/Components/WeightComponent.h"


AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	Collision = CreateDefaultSubobject<UBoxComponent>(FName("Collision"));
	Collision->SetupAttachment(Root);

	VisualsAnchor = CreateDefaultSubobject<USceneComponent>("VisualsAnchor");
	VisualsAnchor->SetupAttachment(Root);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMeshComponent->SetupAttachment(VisualsAnchor);

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

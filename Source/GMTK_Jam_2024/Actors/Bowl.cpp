// Fill out your copyright notice in the Description page of Project Settings.


#include "Bowl.h"

#include "EntityBase.h"
#include "GMTK_Jam_2024/Components/EntityManagerComponent.h"
#include "GMTK_Jam_2024/Components/WeightComponent.h"


ABowl::ABowl()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	WeightComponent = CreateDefaultSubobject<UWeightComponent>("WeightComponent");

	EntityManagerComponent = CreateDefaultSubobject<UEntityManagerComponent>("EntityManager");
}

void ABowl::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(EntityManagerComponent))
	{
		EntityManagerComponent->OnEntityAdded.AddUniqueDynamic(this, &ABowl::HandleEntityAdded);
		EntityManagerComponent->OnEntityRemoved.AddUniqueDynamic(this, &ABowl::HandleEntityRemoved);
	}
}

bool ABowl::AddEntity(AEntityBase* Entity) const
{
	return EntityManagerComponent->AddEntity(Entity);
}

bool ABowl::RemoveEntity(AEntityBase* Entity) const
{
	return EntityManagerComponent->RemoveEntity(Entity);
}

int32 ABowl::GetWeight() const
{
	return WeightComponent->GetCurrentWeight();
}

void ABowl::HandleEntityAdded(UEntityManagerComponent* Component, AEntityBase* Entity)
{
	if(!IsValid(Entity))
	{
		return;
	}

	WeightComponent->AddWeight(Entity->GetCurrentWeight());
}

void ABowl::HandleEntityRemoved(UEntityManagerComponent* Component, AEntityBase* Entity)
{
	if (!IsValid(Entity))
	{
		return;
	}

	WeightComponent->RemoveWeight(Entity->GetCurrentWeight());
}


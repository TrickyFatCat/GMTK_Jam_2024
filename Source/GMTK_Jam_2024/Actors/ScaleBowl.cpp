// Fill out your copyright notice in the Description page of Project Settings.


#include "ScaleBowl.h"

#include "EntityBase.h"
#include "GMTK_Jam_2024/Components/EntityManagerComponent.h"
#include "GMTK_Jam_2024/Components/WeightComponent.h"


AScaleBowl::AScaleBowl()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	WeightComponent = CreateDefaultSubobject<UWeightComponent>("WeightComponent");

	EntityManagerComponent = CreateDefaultSubobject<UEntityManagerComponent>("EntityManager");
}

void AScaleBowl::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(EntityManagerComponent))
	{
		EntityManagerComponent->OnEntityAdded.AddUniqueDynamic(this, &AScaleBowl::HandleEntityAdded);
		EntityManagerComponent->OnEntityRemoved.AddUniqueDynamic(this, &AScaleBowl::HandleEntityRemoved);
	}
}

bool AScaleBowl::AddEntity(AEntityBase* Entity) const
{
	return EntityManagerComponent->AddEntity(Entity);
}

bool AScaleBowl::RemoveEntity(AEntityBase* Entity) const
{
	return EntityManagerComponent->RemoveEntity(Entity);
}

void AScaleBowl::HandleEntityAdded(UEntityManagerComponent* EntityManagerComponent, AEntityBase* Entity)
{
	if(!IsValid(Entity))
	{
		return;
	}

	WeightComponent->AddWeight(Entity->GetCurrentWeight());
}

void AScaleBowl::HandleEntityRemoved(UEntityManagerComponent* EntityManagerComponent, AEntityBase* Entity)
{
	if (!IsValid(Entity))
	{
		return;
	}

	WeightComponent->RemoveWeight(Entity->GetCurrentWeight());
}


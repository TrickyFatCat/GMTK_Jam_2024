// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityManagerComponent.h"

#include "GMTK_Jam_2024/Actors/Entity.h"


UEntityManagerComponent::UEntityManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEntityManagerComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

bool UEntityManagerComponent::AddEntity(AEntity* Entity)
{
	if (!IsValid(Entity) || AddedEntities.Contains(Entity) || AddedEntities.Num() >= MaxEntitiesNum)
	{
		return false;
	}

	AddedEntities.AddUnique(Entity);
	OnEntityAdded.Broadcast(this, Entity);
	return true;
}

bool UEntityManagerComponent::RemoveEntity(AEntity* Entity)
{
	if (!IsValid(Entity) || !AddedEntities.Contains(Entity))
	{
		return false;
	}

	AddedEntities.RemoveSingle(Entity);
	OnEntityRemoved.Broadcast(this, Entity);
	return true;
}

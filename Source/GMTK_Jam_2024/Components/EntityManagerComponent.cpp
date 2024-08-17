// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityManagerComponent.h"

#include "GMTK_Jam_2024/Actors/EntityBase.h"


UEntityManagerComponent::UEntityManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEntityManagerComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

bool UEntityManagerComponent::AddEntity(AEntityBase* Entity)
{
	if (!IsValid(Entity) || AddedEntities.Contains(Entity))
	{
		return false;
	}

	AddedEntities.AddUnique(Entity);
	return true;
}

bool UEntityManagerComponent::RemoveEntity(AEntityBase* Entity)
{
	if (!IsValid(Entity) || !AddedEntities.Contains(Entity))
	{
		return false;
	}

	AddedEntities.RemoveSingle(Entity);
	return true;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "EntitySpawnerComponent.h"

#include "GMTK_Jam_2024/Actors/Entity.h"
#include "Kismet/KismetMathLibrary.h"


UEntitySpawnerComponent::UEntitySpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

AEntity* UEntitySpawnerComponent::SpawnEntity(const FTransform& SpawnTransform)
{
	if (EntityClasses.IsEmpty())
	{
		return nullptr;
	}

	const TSubclassOf<AEntity> EntityClass = EntityClasses.Array()[UKismetMathLibrary::RandomInteger(EntityClasses.Num() - 1)];

	if (!IsValid(EntityClass))
	{
		return nullptr;
	}

	AEntity* NewEntity = GetWorld()->SpawnActorDeferred<AEntity>(EntityClass, SpawnTransform);
	NewEntity->SetOwner(GetOwner());
	NewEntity->FinishSpawning(SpawnTransform);
	OnEntitySpawned.Broadcast(this, NewEntity);
	return NewEntity;
}

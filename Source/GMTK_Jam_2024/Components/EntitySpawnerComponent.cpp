// Fill out your copyright notice in the Description page of Project Settings.


#include "EntitySpawnerComponent.h"

#include "GMTK_Jam_2024/Actors/Entity.h"


UEntitySpawnerComponent::UEntitySpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

AEntity* UEntitySpawnerComponent::SpawnEntity(const FTransform& SpawnTransform)
{
	if (!IsValid(EntityClass))
	{
		return nullptr;
	}

	AEntity* NewEntity = GetWorld()->SpawnActorDeferred<AEntity>(EntityClass, SpawnTransform);
	NewEntity->SetOwner(GetOwner());
	const UCurveFloat* WeightCurve = NewEntity->GetWeightCurve();

	if (IsValid(WeightCurve))
	{
		float MinTime = 0.0;
		float MaxLevel = 1.0;
		WeightCurve->GetTimeRange(MinTime, MaxLevel);
		const int32 NewLevel = FMath::RandRange(0, static_cast<int32>(MaxLevel));
		NewEntity->SetLevel(NewLevel);
	}

	NewEntity->FinishSpawning(SpawnTransform);
	OnEntitySpawned.Broadcast(this, NewEntity);
	return NewEntity;
}

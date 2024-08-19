// Fill out your copyright notice in the Description page of Project Settings.


#include "EntitySpawnerComponent.h"

#include "RoundControllerComponent.h"
#include "Curves/CurveVector.h"
#include "GMTK_Jam_2024/Actors/Entity.h"
#include "GMTK_Jam_2024/Actors/Scales.h"
#include "GMTK_Jam_2024/Core/JamUtils.h"


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
	int32 NewLevel = 0;

	if (IsValid(WeightCurve) && IsValid(LevelCurve))
	{
		int32 CurrentRound = 1;
		AScales* Scales = UJamUtils::GetRegisteredScales(this);

		if (IsValid(Scales))
		{
			CurrentRound = Scales->GetRoundControllerComponent()->GetRoundIndex();
		}

		FVector LevelData = LevelCurve->GetVectorValue(CurrentRound);
		float MinTime = 0.0;
		float ActualMaxLevel = 1.f;
		WeightCurve->GetTimeRange(MinTime, ActualMaxLevel);
		LevelData.X = FMath::Min(LevelData.X, ActualMaxLevel);
		LevelData.Y = FMath::Min(LevelData.Y, ActualMaxLevel);
		UE_LOG(LogTemp, Warning, TEXT("Round: %d | MinLevel: %f | MaxLevel: %f"), CurrentRound, LevelData.X, LevelData.Y);
		NewLevel = FMath::RandRange(static_cast<int32>(LevelData.X), static_cast<int32>(LevelData.Y));
	}
	
	NewEntity->SetLevel(NewLevel);
	NewEntity->FinishSpawning(SpawnTransform);
	OnEntitySpawned.Broadcast(this, NewEntity);
	return NewEntity;
}

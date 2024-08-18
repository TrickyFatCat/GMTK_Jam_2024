// Fill out your copyright notice in the Description page of Project Settings.


#include "Scales.h"

#include "Entity.h"
#include "Bowl.h"
#include "GMTK_Jam_2024/Components/EntityManagerComponent.h"
#include "GMTK_Jam_2024/Components/EntitySpawnerComponent.h"
#include "GMTK_Jam_2024/Components/FailuresCounterComponent.h"
#include "GMTK_Jam_2024/Components/RoundControllerComponent.h"
#include "GMTK_Jam_2024/Components/ScoreManagerComponent.h"
#include "GMTK_Jam_2024/Components/WeightComponent.h"
#include "GMTK_Jam_2024/Core/JamCoreGameMode.h"
#include "GMTK_Jam_2024/Core/JamUtils.h"


AScales::AScales()
{
	PrimaryActorTick.bCanEverTick = true;

	EntitySpawnerComponent = CreateDefaultSubobject<UEntitySpawnerComponent>("EntitySpawner");
	RoundControllerComponent = CreateDefaultSubobject<URoundControllerComponent>("RoundController");
	FailuresCounterComponent = CreateDefaultSubobject<UFailuresCounterComponent>("FailuresCounter");
	ScoreManagerComponent = CreateDefaultSubobject<UScoreManagerComponent>("ScoreManager");
}

void AScales::BeginPlay()
{
	if (IsValid(EntitySpawnerComponent))
	{
		EntitySpawnerComponent->OnEntitySpawned.AddUniqueDynamic(this, &AScales::HandleEntitySpawn);
	}

	if (IsValid(RightBowl))
	{
		RightBowl->GetWeightComponent()->OnWeightAdded.AddUniqueDynamic(this, &AScales::HandleWeightAdded);
		RightBowl->GetWeightComponent()->OnWeightRemoved.AddUniqueDynamic(this, &AScales::HandleWeightRemoved);
		RightBowl->GetEntityManagerComponent()->OnEntityAdded.AddUniqueDynamic(this, &AScales::HandleEntityAdded);
	}

	if (IsValid(LeftBowl))
	{
		LeftBowl->GetWeightComponent()->OnWeightAdded.AddUniqueDynamic(this, &AScales::HandleWeightAdded);
		LeftBowl->GetWeightComponent()->OnWeightRemoved.AddUniqueDynamic(this, &AScales::HandleWeightRemoved);
	}

	if (IsValid(EntitySpawnerComponent))
	{
		RoundControllerComponent->OnRoundStarted.AddUniqueDynamic(this, &AScales::HandleRoundStarted);
		RoundControllerComponent->OnRoundFinished.AddUniqueDynamic(this, &AScales::HandleRoundFinished);
	}

	if (IsValid(FailuresCounterComponent))
	{
		FailuresCounterComponent->OnFailuresThresholdReached.AddUniqueDynamic(
			this, &AScales::HandleFailureThresholdReached);
	}

	AJamCoreGameMode* GameMode = UJamUtils::GetCoreGameMode(this);

	if (IsValid(GameMode))
	{
		GameMode->RegisterScales(this);
		GameMode->OnStateChanged.AddUniqueDynamic(this, &AScales::AScales::HandleGameStateChanged);
	}

	if (IsValid(ScoreManagerComponent))
	{
		UCurveFloat* ScoreCurve = ScoreManagerComponent->GetScoreCurve();

		if (ScoreCurve)
		{
			float MinTime = 0.f;
			ScoreCurve->GetTimeRange(MinTime, FailureBalanceThreshold);
		}
	}

	Super::BeginPlay();
}

bool AScales::AddEntity(AEntity* Entity)
{
	if (!IsValid(Entity) || !IsValid(RightBowl))
	{
		return false;
	}

	return RightBowl->AddEntity(Entity);
}

bool AScales::RemoveEntity(AEntity* Entity)
{
	if (!IsValid(Entity) || !IsValid(RightBowl))
	{
		return false;
	}

	return RightBowl->RemoveEntity(Entity);
}

bool AScales::AddTargetEntity(AEntity* Entity)
{
	if (!IsValid(Entity) || !IsValid(LeftBowl))
	{
		return false;
	}

	return LeftBowl->AddEntity(Entity);
}

void AScales::CalculateBalance()
{
	if (!IsValid(RightBowl) || !IsValid(LeftBowl))
	{
		return;
	}

	const float RightBowlWeight = static_cast<float>(RightBowl->GetWeight());
	const float LeftBowlWeight = static_cast<float>(LeftBowl->GetWeight());
	WeightBalance = LeftBowlWeight <= 0.f ? 0.f : RightBowlWeight / LeftBowlWeight - 1.f;
}

void AScales::HandleGameStateChanged(EGameModeState NewState)
{
	switch (NewState)
	{
	case EGameModeState::InProgress:
		RoundControllerComponent->StartRound();
		break;
	}
}

void AScales::HandleWeightAdded(UWeightComponent* WeightComponent,
                                const int32 NewWeight,
                                const int32 DeltaWeight)
{
	CalculateBalance();
}

void AScales::HandleWeightRemoved(UWeightComponent* WeightComponent,
                                  const int32 NewWeight,
                                  const int32 DeltaWeight)
{
	CalculateBalance();
}

void AScales::HandleEntityAdded(UEntityManagerComponent* Component, AEntity* Entity)
{
	if (!IsValid(Entity))
	{
		return;
	}

	Entity->OnDestroyed.AddDynamic(this, &AScales::HandleEntityDestroyed);
	Entity->AttachToActor(RightBowl, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AScales::HandleEntitySpawn(UEntitySpawnerComponent* Component, AEntity* NewEntity)
{
	NewEntity->DisableEntity();
	NewEntity->AttachToActor(LeftBowl, FAttachmentTransformRules::SnapToTargetIncludingScale);
	AddTargetEntity(NewEntity);
}

void AScales::HandleRoundStarted(URoundControllerComponent* Component, const int32 RoundIdx)
{
	EntitySpawnerComponent->SpawnEntity(LeftBowl->GetTransform());
}

void AScales::HandleRoundFinished(URoundControllerComponent* Component, const int32 RoundIdx)
{
	ScoreManagerComponent->CalculateScore(WeightBalance);
	
	if (FMath::Abs(WeightBalance) >= FailureBalanceThreshold)
	{
		FailuresCounterComponent->IncreaseFailureCount();
	}

	LeftBowl->RemoveAllEntities();
	RightBowl->RemoveAllEntities();

	if (FailuresCounterComponent->CanFail())
	{
		RoundControllerComponent->StartRound();
	}
}

void AScales::HandleFailureThresholdReached(UFailuresCounterComponent* Component)
{
	UJamUtils::GetCoreGameMode(this)->FinishSession(false);
}

void AScales::HandleEntityDestroyed(AActor* Entity)
{
	RemoveEntity(Cast<AEntity>(Entity));
}

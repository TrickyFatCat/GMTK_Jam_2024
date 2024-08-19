// Fill out your copyright notice in the Description page of Project Settings.


#include "Bowl.h"

#include "Entity.h"
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

void ABowl::OnConstruction(const FTransform& Transform)
{
	if (IsValid(EntityManagerComponent))
	{
		SizeX = EntityManagerComponent->GetMaxEntitiesNum() * 0.5;
		SizeX = FMath::Max(SizeX, 1);
		SizeY = EntityManagerComponent->GetMaxEntitiesNum() * 0.5;
		SizeY = FMath::Max(SizeY, 1);
	}

	const FVector ForwardVector = GetActorForwardVector();
	const FVector RightVector = GetActorRightVector();
	FVector NewLocation = FVector::ZeroVector;
	EntityOffsets.Empty();

	if (SizeX > 1 || SizeY > 1)
		for (int32 x = 0; x < SizeX; x++)
		{
			for (int32 y = 0; y < SizeY; y++)
			{
				NewLocation.X = SectorSize.X * x - SectorSize.X * SizeX * 0.25f;
				NewLocation.Y = SectorSize.Y * y - SectorSize.Y * SizeY * 0.25f;
				EntityOffsets.Emplace(NewLocation);
			}
		}

	Super::OnConstruction(Transform);
}

void ABowl::BeginPlay()
{
	if (IsValid(EntityManagerComponent))
	{
		EntityManagerComponent->OnEntityAdded.AddUniqueDynamic(this, &ABowl::HandleEntityAdded);
		EntityManagerComponent->OnEntityRemoved.AddUniqueDynamic(this, &ABowl::HandleEntityRemoved);
	}

	Super::BeginPlay();
}

bool ABowl::AddEntity(AEntity* Entity) const
{
	return EntityManagerComponent->AddEntity(Entity);
}

bool ABowl::RemoveEntity(AEntity* Entity) const
{
	return EntityManagerComponent->RemoveEntity(Entity, true);
}

void ABowl::RemoveAllEntities()
{
	EntityManagerComponent->RemoveAllEntities(true);
}

int32 ABowl::GetWeight() const
{
	return WeightComponent->GetCurrentWeight();
}

void ABowl::HandleEntityAdded(UEntityManagerComponent* Component, AEntity* Entity)
{
	if (!IsValid(Entity))
	{
		return;
	}

	Entity->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	const FVector LocationOffset = EntityOffsets.IsEmpty()
		                               ? FVector::ZeroVector
		                               : EntityOffsets[Component->GetAddedEntitiesNum() - 1];
	Entity->AddActorLocalOffset(LocationOffset);
	WeightComponent->AddWeight(Entity->GetCurrentWeight());
}

void ABowl::HandleEntityRemoved(UEntityManagerComponent* Component, AEntity* Entity)
{
	if (!IsValid(Entity))
	{
		return;
	}

	WeightComponent->RemoveWeight(Entity->GetCurrentWeight());
}

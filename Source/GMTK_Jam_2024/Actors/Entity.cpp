// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"

#include "Components/BoxComponent.h"
#include "GMTK_Jam_2024/Components/EntityStateControllerComponent.h"
#include "GMTK_Jam_2024/Components/WeightComponent.h"


AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Root);

	VisualsAnchor = CreateDefaultSubobject<USceneComponent>("VisualsAnchor");
	VisualsAnchor->SetupAttachment(Root);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(VisualsAnchor);

	WeightComponent = CreateDefaultSubobject<UWeightComponent>("Weight");
	EntityStateControllerComponent = CreateDefaultSubobject<UEntityStateControllerComponent>("EntityStateController");
}

int32 AEntity::GetCurrentWeight() const
{
	if (!IsValid(WeightComponent))
	{
		return -1;
	}

	return WeightComponent->GetCurrentWeight();
}

EEntityState AEntity::GetCurrentState() const
{
	return EntityStateControllerComponent->GetCurrentState();
}

void AEntity::ActivateEntity()
{
	EntityStateControllerComponent->Activate();
}

void AEntity::DisableEntity()
{
	EntityStateControllerComponent->DisableEntity();
}

void AEntity::HandleStateChanged(UEntityStateControllerComponent* Component, const EEntityState NewState)
{
	switch (NewState)
	{
	case EEntityState::Disabled:
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	}
}

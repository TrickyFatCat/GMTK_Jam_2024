// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"

#include "Scales.h"
#include "Components/BoxComponent.h"
#include "GMTK_Jam_2024/Components/EntityStateControllerComponent.h"
#include "GMTK_Jam_2024/Components/WeightComponent.h"
#include "GMTK_Jam_2024/Core/JamCoreGameMode.h"
#include "GMTK_Jam_2024/Core/JamUtils.h"


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

void AEntity::BeginPlay()
{
	OnClicked.AddUniqueDynamic(this, &AEntity::AEntity::HandleMouseClick);

	EntityStateControllerComponent->OnStateChanged.AddDynamic(this, &AEntity::AEntity::HandleStateChanged);

	Super::BeginPlay();
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

void AEntity::HandleMouseClick(AActor* TouchedActor, FKey ButtonPressed)
{
	switch (EntityStateControllerComponent->GetCurrentState())
	{
	case EEntityState::Inactive:
		EntityStateControllerComponent->ActivateEntity();
		break;

	case EEntityState::Active:
		Destroy();
		break;
	}
}

void AEntity::HandleStateChanged(UEntityStateControllerComponent* Component, const EEntityState NewState)
{
	AJamCoreGameMode* GameMode = UJamUtils::GetCoreGameMode(this);
	
	switch (NewState)
	{
	case EEntityState::Active:

		if (IsValid(GameMode))
		{
			AScales* Scales = GameMode->GetScales();

			if (IsValid(Scales))
			{
				Scales->AddEntity(this);
			}
		}
		break;

	case EEntityState::Disabled:
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	}
}

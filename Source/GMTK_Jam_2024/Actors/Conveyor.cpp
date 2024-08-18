// Fill out your copyright notice in the Description page of Project Settings.


#include "Conveyor.h"

#include "Entity.h"
#include "TrickyGameModeBase.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GMTK_Jam_2024/Components/EntityManagerComponent.h"
#include "GMTK_Jam_2024/Components/EntitySpawnerComponent.h"
#include "GMTK_Jam_2024/Components/EntityStateControllerComponent.h"
#include "GMTK_Jam_2024/Core/JamCoreGameMode.h"
#include "GMTK_Jam_2024/Core/JamUtils.h"


AConveyor::AConveyor()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Root->SetMobility(EComponentMobility::Static);

	StartMesh = CreateDefaultSubobject<UStaticMeshComponent>("StartMesh");
	StartMesh->SetupAttachment(Root);
	StartMesh->SetMobility(EComponentMobility::Static);

	MiddleMesh = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>("MiddleMesh");
	MiddleMesh->SetupAttachment(Root);
	MiddleMesh->SetMobility(EComponentMobility::Static);

	EndMesh = CreateDefaultSubobject<UStaticMeshComponent>("EndMesh");
	EndMesh->SetupAttachment(Root);
	EndMesh->SetMobility(EComponentMobility::Static);

	EntitySpawnerComponent = CreateDefaultSubobject<UEntitySpawnerComponent>("EntitySpawnerComponent");
	EntityManagerComponent = CreateDefaultSubobject<UEntityManagerComponent>("EntityManagerComponent");
}

void AConveyor::OnConstruction(const FTransform& Transform)
{
	TArray<FTransform> SectionsTransforms;
	UJamUtils::CalculateSectionTransforms(SectionsNum, SectionOffset, SectionRotation, SectionsTransforms);
	MiddleMesh->ClearInstances();
	MiddleMesh->AddInstances(SectionsTransforms, false);
	EndMesh->SetRelativeTransform(SectionsTransforms.Last());
	Super::OnConstruction(Transform);
}

void AConveyor::BeginPlay()
{
	AJamCoreGameMode* GameMode = UJamUtils::GetCoreGameMode(this);

	if (IsValid(GameMode))
	{
		GameMode->OnStateChanged.AddUniqueDynamic(this, &AConveyor::HandleGameStateChanged);
	}

	if (IsValid(EntitySpawnerComponent))
	{
		EntitySpawnerComponent->OnEntitySpawned.AddUniqueDynamic(this, &AConveyor::HandleEntitySpawn);
	}

	if (IsValid(EntityManagerComponent))
	{
		EntityManagerComponent->OnEntityAdded.AddUniqueDynamic(this, &AConveyor::HandleEntityAdded);
		EntityManagerComponent->OnEntityRemoved.AddUniqueDynamic(this, &AConveyor::HandleEntityRemoved);
	}
	Super::BeginPlay();
}

void AConveyor::Tick(float DeltaSeconds)
{

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	
	if (!AttachedActors.IsEmpty())
	{
		for (const auto AttachedActor : AttachedActors)
		{
			AttachedActor->AddActorWorldOffset(GetActorForwardVector() * ConveyorSpeed * DeltaSeconds);
		}
	}
}

void AConveyor::HandleGameStateChanged(EGameModeState NewState)
{
	FTimerManager& TimerManager = GetWorldTimerManager();
	
	switch (NewState)
	{
	case EGameModeState::InProgress:
		SpawnEntity();
		TimerManager.SetTimer(SpawnTimer, this, &AConveyor::SpawnEntity, SpawnDelay, true);
		break;

	default:
		TimerManager.ClearTimer(SpawnTimer);
		break;
	}
}

void AConveyor::SpawnEntity()
{
	FTransform SpawnTransform = GetActorTransform();
	FVector SpawnLocation = SpawnTransform.GetLocation() + SpawnOffset;
	SpawnTransform.SetLocation(SpawnLocation);
	EntitySpawnerComponent->SpawnEntity(SpawnTransform);
}

void AConveyor::HandleEntitySpawn(UEntitySpawnerComponent* Component, AEntity* NewEntity)
{
	EntityManagerComponent->AddEntity(NewEntity);
}

void AConveyor::HandleEntityStateChanged(UEntityStateControllerComponent* Component, EEntityState NewState)
{
	switch (NewState)
	{
	case EEntityState::Active:
		EntityManagerComponent->RemoveEntity(Cast<AEntity>(Component->GetOwner()));
		break;
	}
}

void AConveyor::HandleEntityAdded(UEntityManagerComponent* Component, AEntity* Entity)
{
	Entity->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	Entity->GetEntityStateControllerComponent()->OnStateChanged.AddUniqueDynamic(this, &AConveyor::HandleEntityStateChanged);
	Entity->SetLifeSpan((SectionOffset * SectionsNum) / ConveyorSpeed);
	Entity->OnDestroyed.AddUniqueDynamic(this, &AConveyor::AConveyor::HandleEntityDestroyed);
}

void AConveyor::HandleEntityRemoved(UEntityManagerComponent* Component, AEntity* Entity)
{
	Entity->GetEntityStateControllerComponent()->OnStateChanged.RemoveDynamic(this, &AConveyor::HandleEntityStateChanged);
	Entity->OnDestroyed.RemoveDynamic(this, &AConveyor::HandleEntityDestroyed);
}

void AConveyor::HandleEntityDestroyed(AActor* Entity)
{
	EntityManagerComponent->RemoveEntity(Cast<AEntity>(Entity));
}

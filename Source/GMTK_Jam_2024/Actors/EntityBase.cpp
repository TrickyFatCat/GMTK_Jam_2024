// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityBase.h"

#include "Components/BoxComponent.h"


AEntityBase::AEntityBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>(FName("Collision"));
	SetRootComponent(Collision);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

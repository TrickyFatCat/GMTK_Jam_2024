// Fill out your copyright notice in the Description page of Project Settings.


#include "WeightComponent.h"


UWeightComponent::UWeightComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UWeightComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UWeightComponent::AddWeight(const int32 DeltaWeight)
{
	if (DeltaWeight <= 0)
	{
		return;
	}

	CurrentWeight += DeltaWeight;
	OnWeightAdded.Broadcast(this, CurrentWeight, DeltaWeight);
}

void UWeightComponent::RemoveWeight(const int32 DeltaWeight)
{
	if (DeltaWeight <= 0)
	{
		return;
	}

	CurrentWeight -= DeltaWeight;
	CurrentWeight = FMath::Max(CurrentWeight, 0);
	OnWeightRemoved.Broadcast(this, CurrentWeight, DeltaWeight);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "FailuresCounterComponent.h"


UFailuresCounterComponent::UFailuresCounterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFailuresCounterComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UFailuresCounterComponent::IncreaseFailureCount()
{
	FailuresNumber += 1;
	OnFailuresNumberIncreased.Broadcast(this, FailuresNumber);

	if (FailuresNumber > FailuresThreshold)
	{
		OnFailuresThresholdReached.Broadcast(this);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "RoundControllerComponent.h"


URoundControllerComponent::URoundControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URoundControllerComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void URoundControllerComponent::StartRound()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(RoundTimer))
	{
		return;
	}

	RoundIndex += 1;
	TimerManager.SetTimer(RoundTimer, this, &URoundControllerComponent::FinishRound, RoundDuration, false);
	OnRoundStarted.Broadcast(this, RoundIndex);
}

void URoundControllerComponent::FinishRound()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(RoundTimer))
	{
		TimerManager.ClearTimer(RoundTimer);
	}
	
	OnRoundFinished.Broadcast(this, RoundIndex);
}

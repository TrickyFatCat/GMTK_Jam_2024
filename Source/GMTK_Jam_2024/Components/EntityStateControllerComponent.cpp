// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityStateControllerComponent.h"


UEntityStateControllerComponent::UEntityStateControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UEntityStateControllerComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UEntityStateControllerComponent::ActivateEntity()
{
	ChangeState(EEntityState::Active);
}

void UEntityStateControllerComponent::DisableEntity()
{
	ChangeState(EEntityState::Disabled);
}

void UEntityStateControllerComponent::ChangeState(const EEntityState NewState)
{
	if (CurrentState == NewState)
	{
		return;
	}

	CurrentState = NewState;
	OnStateChanged.Broadcast(this, NewState);
}

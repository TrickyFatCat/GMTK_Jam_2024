// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityStateControllerComponent.generated.h"

UENUM()
enum class EEntityState : uint8
{
	Inactive,
	Active,
	Disabled
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateChangedDynamicSignature,
                                             UEntityStateControllerComponent*, Component,
                                             EEntityState, NewState);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GMTK_JAM_2024_API UEntityStateControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEntityStateControllerComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnStateChangedDynamicSignature OnStateChanged;

	UFUNCTION(BlueprintGetter)
	EEntityState GetEntityState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable)
	void ActivateEntity();

	UFUNCTION(BlueprintCallable)
	void DisableEntity();

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetCurrentState)
	EEntityState CurrentState = EEntityState::Inactive;

	UFUNCTION()
	void ChangeState(const EEntityState NewState);
};

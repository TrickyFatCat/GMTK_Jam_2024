// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RoundControllerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRoundStartedDynamicSignature,
                                             URoundControllerComponent*, Component,
                                             const int32, RoundIdx);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRoundFinishedDynamicSignature,
                                             URoundControllerComponent*, Component,
                                             const int32, RoundIdx);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GMTK_JAM_2024_API URoundControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URoundControllerComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnRoundStartedDynamicSignature OnRoundStarted;

	UPROPERTY(BlueprintAssignable)
	FOnRoundFinishedDynamicSignature OnRoundFinished;

	UFUNCTION(BlueprintCallable)
	void StartRound();

	UFUNCTION(BlueprintGetter)
	int32 GetRoundIndex() const { return RoundIndex; }

	UFUNCTION(BlueprintGetter)
	FTimerHandle GetRoundTimer() const { return RoundTimer; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RoundDuration = 10.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetRoundIndex)
	int32 RoundIndex = 0;

	UPROPERTY(BlueprintGetter=GetRoundTimer)
	FTimerHandle RoundTimer;

	UFUNCTION()
	void FinishRound();
};

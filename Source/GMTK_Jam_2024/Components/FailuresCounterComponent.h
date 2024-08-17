// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FailuresCounterComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFailuresNumberIncreasedDynamicSignature,
                                             UFailuresCounterComponent*, Componet,
                                             const int32, NewFailureNumber);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFailuresThresholdReachedDynamicSiganture,
                                            UFailuresCounterComponent*, Component);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GMTK_JAM_2024_API UFailuresCounterComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFailuresCounterComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnFailuresNumberIncreasedDynamicSignature OnFailuresNumberIncreased;

	UPROPERTY(BlueprintAssignable)
	FOnFailuresThresholdReachedDynamicSiganture OnFailuresThresholdReached;

	UFUNCTION(BlueprintCallable)
	void IncreaseFailureCount();

	UFUNCTION(BlueprintGetter)
	int32 GetFailuresNumber() const { return FailuresNumber; }

	UFUNCTION(BlueprintGetter)
	int32 GetFailuresThreshold() const { return FailuresThreshold; }

	UFUNCTION(BlueprintPure)
	bool CanFail() const { return FailuresNumber < FailuresThreshold; }

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetFailuresNumber)
	int32 FailuresNumber = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetFailuresThreshold)
	int32 FailuresThreshold = 5;
};

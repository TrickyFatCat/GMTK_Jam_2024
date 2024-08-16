// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeightComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWeightAddedDynamicSignature,
                                               UWeightComponent*, Component,
                                               const int32, NewWeight,
                                               const int32, DeltaWeight);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWeightRemovedDynamicSignature,
                                               UWeightComponent*, Component,
                                               const int32, NewWeight,
                                               const int32, DeltaWeight);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GMTK_JAM_2024_API UWeightComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeightComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnWeightAddedDynamicSignature OnWeightAdded;

	UPROPERTY(BlueprintAssignable)
	FOnWeightRemovedDynamicSignature OnWeightRemoved;

	UFUNCTION(BlueprintCallable)
	void AddWeight(const int32 DeltaWeight);

	UFUNCTION(BlueprintCallable)
	void RemoveWeight(const int32 DeltaWeight);

	UFUNCTION(BlueprintGetter)
	int32 GetCurrentWeight() const { return CurrentWeight; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetCurrentWeight, meta=(ClampMin="0"))
	int32 CurrentWeight = 0;
};

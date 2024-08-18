// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnScoreUpdatedDynamicSignature,
                                               UScoreManagerComponent*, Component,
                                               int32, NewScore,
                                               int32, DeltaScore);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GMTK_JAM_2024_API UScoreManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UScoreManagerComponent();

public:
	UPROPERTY(BlueprintAssignable)
	FOnScoreUpdatedDynamicSignature OnScoreUpdated;
	
	UFUNCTION(BlueprintGetter)
	int32 GetScore() const { return Score; }

	UFUNCTION(BlueprintCallable)
	void CalculateScore(const float BalanceWeight);

	UFUNCTION(BlueprintGetter)
	UCurveFloat* GetScoreCurve() const { return ScoreCurve; }

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetScore)
	int32 Score = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetScoreCurve)
	UCurveFloat* ScoreCurve = nullptr;
};

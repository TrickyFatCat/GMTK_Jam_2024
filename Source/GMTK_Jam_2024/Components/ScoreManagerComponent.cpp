// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreManagerComponent.h"


UScoreManagerComponent::UScoreManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UScoreManagerComponent::CalculateScore(const float BalanceWeight)
{
	int32 NewScore = 1;

	if (IsValid(ScoreCurve))
	{
		NewScore = ScoreCurve->GetFloatValue(FMath::Abs(BalanceWeight));
	}

	Score += NewScore;
	OnScoreUpdated.Broadcast(this, Score, NewScore);
}
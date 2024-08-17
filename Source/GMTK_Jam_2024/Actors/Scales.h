// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Scales.generated.h"

class UFailuresCounterComponent;
class URoundControllerComponent;
class UEntitySpawnerComponent;
class UWeightComponent;
class UEntityManagerComponent;
class AEntity;
class ABowl;

UCLASS()
class GMTK_JAM_2024_API AScales : public AActor
{
	GENERATED_BODY()

public:
	AScales();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	bool AddEntity(AEntity* Entity);
	
	UFUNCTION(BlueprintCallable)
	bool RemoveEntity(AEntity* Entity);

	UFUNCTION(BlueprintGetter)
	float GetWeightBalance() const { return WeightBalance; }

	UFUNCTION(BlueprintGetter)
	URoundControllerComponent* GetRoundControllerComponent() const { return RoundControllerComponent; }

	UFUNCTION(BlueprintGetter)
	UFailuresCounterComponent* GetFailuresCounterComponent() const { return FailuresCounterComponent; }
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UEntitySpawnerComponent> EntitySpawnerComponent = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintGetter=GetRoundControllerComponent)
	TObjectPtr<URoundControllerComponent> RoundControllerComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintGetter=GetFailuresCounterComponent)
	TObjectPtr<UFailuresCounterComponent> FailuresCounterComponent = nullptr;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	ABowl* LeftBowl = nullptr;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	ABowl* RightBowl = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin="0.0", ClampMax="1.0"))
	float FailureBalanceThreshold = 0.5;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetWeightBalance)
	float WeightBalance = 0.f;

	UFUNCTION(BlueprintCallable)
	bool AddTargetEntity(AEntity* Entity);
	
private:
	UFUNCTION()
	void CalculateBalance();

	UFUNCTION()
	void HandleGameStateChanged(EGameModeState NewState);
	
	UFUNCTION()
	void HandleWeightAdded(UWeightComponent* WeightComponent, const int32 NewWeight, const int32 DeltaWeight);

	UFUNCTION()
	void HandleWeightRemoved(UWeightComponent* WeightComponent, const int32 NewWeight, const int32 DeltaWeight);

	UFUNCTION()
	void HandleEntitySpawn(UEntitySpawnerComponent* Component, AEntity* NewEntity);

	UFUNCTION()
	void HandleRoundStarted(URoundControllerComponent* Component, const int32 RoundIdx);
	
	UFUNCTION()
	void HandleRoundFinished(URoundControllerComponent* Component, const int32 RoundIdx);

	UFUNCTION()
	void HandleFailureThresholdReached(UFailuresCounterComponent* Component);

	UFUNCTION()
	void HandleEntityDestroyed(AActor* Entity);
};

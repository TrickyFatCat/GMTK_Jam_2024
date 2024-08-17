// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Scales.generated.h"

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
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UEntitySpawnerComponent> EntitySpawnerComponent;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	ABowl* LeftBowl = nullptr;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	ABowl* RightBowl = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetWeightBalance)
	float WeightBalance = 0.0f;

	UFUNCTION(BlueprintCallable)
	bool AddTargetEntity(AEntity* Entity);
	
	UFUNCTION(BlueprintCallable)
	bool RemoveTargetEntity(AEntity* Entity);

private:
	UFUNCTION()
	void CalculateBalance();
	
	UFUNCTION()
	void HandleWeightAdded(UWeightComponent* WeightComponent, const int32 NewWeight, const int32 DeltaWeight);

	UFUNCTION()
	void HandleWeightRemoved(UWeightComponent* WeightComponent, const int32 NewWeight, const int32 DeltaWeight);

	UFUNCTION()
	void HandleEntitySpawn(UEntitySpawnerComponent* Component, AEntity* NewEntity);
};

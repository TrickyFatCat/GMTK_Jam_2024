﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bowl.generated.h"

class UWeightComponent;
class UEntityManagerComponent;
class AEntity;

UCLASS()
class GMTK_JAM_2024_API ABowl : public AActor
{
	GENERATED_BODY()

public:
	ABowl();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	bool AddEntity(AEntity* Entity) const;

	UFUNCTION(BlueprintCallable)
	bool RemoveEntity(AEntity* Entity) const;

	UFUNCTION(BlueprintCallable)
	void RemoveAllEntities();

	UFUNCTION(BlueprintPure)
	int32 GetWeight() const;

	UFUNCTION(BlueprintGetter)
	UWeightComponent* GetWeightComponent() const { return WeightComponent; }

	UFUNCTION(BlueprintGetter)
	UEntityManagerComponent* GetEntityManagerComponent() const { return EntityManagerComponent; }

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintGetter=GetWeightComponent)
	TObjectPtr<UWeightComponent> WeightComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintGetter=GetEntityManagerComponent)
	TObjectPtr<UEntityManagerComponent> EntityManagerComponent = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<FVector> EntityOffsets;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int32 SizeX = 1;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int32 SizeY = 1;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	FVector2D SectorSize = FVector2D(200.f, 200.f);

private:
	UFUNCTION()
	void HandleEntityAdded(UEntityManagerComponent* Component, AEntity* Entity);

	UFUNCTION()
	void HandleEntityRemoved(UEntityManagerComponent* Component, AEntity* Entity);
};

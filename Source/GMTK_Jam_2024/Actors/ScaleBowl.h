// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScaleBowl.generated.h"

class UEntityManagerComponent;
class AEntityBase;

UCLASS()
class GMTK_JAM_2024_API AScaleBowl : public AActor
{
	GENERATED_BODY()

public:
	AScaleBowl();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	bool AddEntity(AEntityBase* Entity) const;

	UFUNCTION(BlueprintCallable)
	bool RemoveEntity(AEntityBase* Entity) const;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UWeightComponent> WeightComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UEntityManagerComponent> EntityManagerComponent = nullptr;

private:
	UFUNCTION()
	void HandleEntityAdded(UEntityManagerComponent* EntityManagerComponent, AEntityBase* Entity);

	UFUNCTION()
	void HandleEntityRemoved(UEntityManagerComponent* EntityManagerComponent, AEntityBase* Entity);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EntityBase.generated.h"

class UWeightComponent;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class GMTK_JAM_2024_API AEntityBase : public AActor
{
	GENERATED_BODY()

public:
	AEntityBase();

	UFUNCTION(BlueprintPure)
	int32 GetCurrentWeight() const;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> Collision = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UWeightComponent> WeightComponent = nullptr;
};

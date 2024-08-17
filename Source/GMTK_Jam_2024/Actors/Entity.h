// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Entity.generated.h"

class UWeightComponent;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class GMTK_JAM_2024_API AEntity : public AActor
{
	GENERATED_BODY()

public:
	AEntity();

	UFUNCTION(BlueprintPure)
	int32 GetCurrentWeight() const;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> Collision = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> VisualsAnchor = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UWeightComponent> WeightComponent = nullptr;
};

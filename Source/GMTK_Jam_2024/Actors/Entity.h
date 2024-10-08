﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Entity.generated.h"

enum class EEntityState : uint8;
class UEntityStateControllerComponent;
class UWeightComponent;
class UBoxComponent;
class UStaticMeshComponent;

USTRUCT(Blueprintable)
struct FEntityParams
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UStaticMesh*> StaticMeshes;
};

UCLASS()
class GMTK_JAM_2024_API AEntity : public AActor
{
	GENERATED_BODY()

public:
	AEntity();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	int32 GetCurrentWeight() const;

	UFUNCTION(BlueprintPure)
	EEntityState GetCurrentState() const;

	UFUNCTION(BlueprintCallable)
	void ActivateEntity();

	UFUNCTION(BlueprintCallable)
	void DisableEntity();

	UFUNCTION(BlueprintGetter)
	UEntityStateControllerComponent* GetEntityStateControllerComponent() const { return EntityStateControllerComponent; }

	UFUNCTION(BlueprintCallable)
	void SetLevel(const int32 NewLevel);

	UFUNCTION(BlueprintGetter)
	UCurveFloat* GetWeightCurve() const { return WeightCurve; }

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

	UPROPERTY(VisibleDefaultsOnly, BlueprintGetter=GetEntityStateControllerComponent)
	TObjectPtr<UEntityStateControllerComponent> EntityStateControllerComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetWeightCurve)
	UCurveFloat* WeightCurve = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FEntityParams> EntityParams;

private:
	UFUNCTION()
	void HandleMouseClick(AActor* TouchedActor, FKey ButtonPressed);
	
	UFUNCTION()
	void HandleStateChanged(UEntityStateControllerComponent* Component, EEntityState NewState);
};

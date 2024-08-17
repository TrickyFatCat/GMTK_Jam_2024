// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntitySpawnerComponent.generated.h"

class AEntity;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEntitySpawnedDynamicSignatre,
                                             UEntitySpawnerComponent*, Component,
                                             AEntity*, Entity);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GMTK_JAM_2024_API UEntitySpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEntitySpawnerComponent();

	UPROPERTY(BlueprintAssignable)
	FOnEntitySpawnedDynamicSignatre OnEntitySpawned;
	
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="SpawnTransform"))
	AEntity* SpawnEntity(const FTransform& SpawnTransform);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSet<TSubclassOf<AEntity>> EntityClasses;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityManagerComponent.generated.h"


class AEntityBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEntityAddedDynamicSignature,
                                             UEntityManagerComponent*, Component,
                                             AEntityBase*, Entity);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEntityRemovedDynamicSignature,
                                             UEntityManagerComponent*, Component,
                                             AEntityBase*, Entity);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GMTK_JAM_2024_API UEntityManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEntityManagerComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnEntityAddedDynamicSignature OnEntityAdded;

	UPROPERTY(BlueprintAssignable)
	FOnEntityRemovedDynamicSignature OnEntityRemoved;
	
	UFUNCTION(BlueprintCallable)
	bool AddEntity(AEntityBase* Entity);

	UFUNCTION(BlueprintCallable)
	bool RemoveEntity(AEntityBase* Entity);

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<AEntityBase*> AddedEntities;
};

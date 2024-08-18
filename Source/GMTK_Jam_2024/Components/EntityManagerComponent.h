// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityManagerComponent.generated.h"


class AEntity;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEntityAddedDynamicSignature,
                                             UEntityManagerComponent*, Component,
                                             AEntity*, Entity);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEntityRemovedDynamicSignature,
                                             UEntityManagerComponent*, Component,
                                             AEntity*, Entity);

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
	bool AddEntity(AEntity* Entity);

	UFUNCTION(BlueprintCallable)
	bool RemoveEntity(AEntity* Entity, const bool bDestroy = false);

	UFUNCTION(BlueprintCallable)
	void RemoveAllEntities(const bool bDestroy = false);

	UFUNCTION(BlueprintGetter)
	TArray<AEntity*> GetAddedEntities() const { return AddedEntities; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxEntitiesNum = 1;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetAddedEntities)
	TArray<AEntity*> AddedEntities;
};

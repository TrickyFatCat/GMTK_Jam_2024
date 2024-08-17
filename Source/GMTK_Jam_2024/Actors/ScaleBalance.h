// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScaleBalance.generated.h"

class AEntityBase;
class AScaleBowl;

UCLASS()
class GMTK_JAM_2024_API AScaleBalance : public AActor
{
	GENERATED_BODY()

public:
	AScaleBalance();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	bool AddEntity(AEntityBase* Entity) const;
	
	UFUNCTION(BlueprintCallable)
	bool RemoveEntity(AEntityBase* Entity) const;
	
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	AScaleBowl* LeftScaleBowl = nullptr;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	AScaleBowl* RightScaleBowl = nullptr;
};

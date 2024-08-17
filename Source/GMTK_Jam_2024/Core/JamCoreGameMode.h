// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrickyGameModeBase.h"

#include "JamCoreGameMode.generated.h"

class AScales;
/**
 * 
 */
UCLASS()
class GMTK_JAM_2024_API AJamCoreGameMode : public ATrickyGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintGetter)
	AScales* GetScales() const { return Scales; }

	UFUNCTION()
	void RegisterScales(AScales* NewScales);
	
protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetScales)
	AScales* Scales = nullptr;
};

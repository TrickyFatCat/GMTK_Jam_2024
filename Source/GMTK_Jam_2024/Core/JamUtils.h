// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JamUtils.generated.h"

class URoundControllerComponent;
class AJamCoreGameMode;
/**
 * 
 */
UCLASS()
class GMTK_JAM_2024_API UJamUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObj", DefaultToSelf))
	static AScales* GetRegisteredScales(const UObject* WorldContextObj);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObj", DefaultToSelf))
	static AJamCoreGameMode* GetCoreGameMode(const UObject* WorldContextObj);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObj", DefaultToSelf))
	static URoundControllerComponent* GetRoundControllerComponent(const UObject* WorldContextObj);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Conveyor.generated.h"

enum class EEntityState : uint8;
class UEntityStateControllerComponent;
enum class EGameModeState : uint8;
class UEntityManagerComponent;
class UEntitySpawnerComponent;
class USceneComponent;
class UStaticMeshComponent;
class UHierarchicalInstancedStaticMeshComponent;

UCLASS()
class GMTK_JAM_2024_API AConveyor : public AActor
{
	GENERATED_BODY()

public:
	AConveyor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StartMesh = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> MiddleMesh = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> EndMesh = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UEntitySpawnerComponent> EntitySpawnerComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UEntityManagerComponent> EntityManagerComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SpawnDelay = 1.0f;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle SpawnTimer;

private:
	UFUNCTION()
	void HandleGameStateChanged(EGameModeState NewState);

	UFUNCTION()
	void SpawnEntity();

	UFUNCTION()
	void HandleEntitySpawn(UEntitySpawnerComponent* Component, AEntity* NewEntity);

	UFUNCTION()
	void HandleEntityStateChanged(UEntityStateControllerComponent* Component, EEntityState NewState);

	UFUNCTION()
	void HandleEntityAdded(UEntityManagerComponent* Component, AEntity* Entity);
	
	UFUNCTION()
	void HandleEntityRemoved(UEntityManagerComponent* Component, AEntity* Entity);
};

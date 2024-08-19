// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Conveyor.generated.h"

class AScales;
class URoundControllerComponent;
class UCurveVector;
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
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

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

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	AScales* Scales = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector SpawnOffset = FVector::Zero();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCurveVector* BalanceCurve = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SpawnDelay = 1.0f;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle SpawnTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ConveyorSpeed = 400.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SectionsNum = 9;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SectionOffset = 400.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FRotator SectionRotation = FRotator(0, -90, 0);

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

	UFUNCTION()
	void HandleEntityDestroyed(AActor* Entity);

	UFUNCTION()
	void HandleRoundStarted(URoundControllerComponent* Component, const int32 RoundIdx);
};


// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "SphereActor.h"
#include "GameFramework/GameModeBase.h"
#include "TestTaskGameMode.generated.h"

class ATestTaskPlayerState;
UCLASS(minimalapi)
class ATestTaskGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestTaskGameMode();
	
	virtual void BeginPlay() override;

	//Blueprint of spawn sphere
	UPROPERTY(EditAnywhere, Category = "Game")
	TSubclassOf<class AActor> SphereToSpawn;

	int32 GetCurrentWave() const { return CurrentWave; };

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FDistanceData DistanceData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game");
	FQuantityData QuantityData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FScaleData SphereScaleData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	float IncreaseRadiusPercentEveryRound = 0.05f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	float IncreaseNumSpherePercentEveryRound = 0.1f;

private:
	int32 CurrentWave = 0;
	
	FVector StartLocation;

	//Spawn sphere in player location
	void SpawnSpheres();

	//Function for delegate OnSphereDestroy
	void OnSphereDestroy(FVector Location);

	//+1 to score and check next wave
	void AddScore();
	void CheckScoreToNextWave(ATestTaskPlayerState* PlayerState);

	//Restart spheres and increase spawn radius and quantity of spheres
	void NextWave();
	void IncreaseRadiusAndNum();
	
	void DeleteRestSpheres() const;

	//Check distance among other spheres
	bool CheckDistance(TArray<FVector>& SphereLocations, FVector SpawnLocation) const;
};




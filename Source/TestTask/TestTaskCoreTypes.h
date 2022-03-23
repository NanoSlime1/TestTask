#pragma once
#include "TestTaskCoreTypes.generated.h"

class ASphereActor;

//Delegate for Sphere, for main code in GameMode
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSphereDestroySignature, FVector);

USTRUCT(BlueprintType)
struct FQuantityData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ToolTip = "This is need be > than QuantityOfSpheresForDestroy!"));
	int32 QuantityStartSpheres = 15;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ToolTip = "This is need be < than QuantityStartSpheres!"))
	int32 QuantityOfSpheresForDestroy = 10;
	
};

USTRUCT(BlueprintType)
struct FDistanceData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	float StartRadius = 2000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	float MinimalDistanceAmongSphere = 80.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	float RadiusForDestroy = 1500.0f;
	
};

USTRUCT(BlueprintType)
struct FScaleData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	float MinimalScale = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	float StepDecreasingScale = 0.05f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	float StartScale = 1.0f;
	
};


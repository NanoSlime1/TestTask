// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TestTaskPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API ATestTaskPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void AddScore() { Score++; }
	int32 GetScore() const { return Score; }

	void ResetScore() { Score = 0; }

private:
	//Quantity of the destroy spheres in smaller radius
	int32 Score = 0;
	
};

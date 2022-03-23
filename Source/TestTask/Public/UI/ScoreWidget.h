// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

class ATestTaskPlayerState;
class ATestTaskGameMode;
/**
 * 
 */
UCLASS()
class TESTTASK_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentWave() const;

private:
	ATestTaskGameMode* GetTestTaskGameMode() const;
	ATestTaskPlayerState* GetTestTaskPlayerState() const;
	
};

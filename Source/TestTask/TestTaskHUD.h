// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TestTaskHUD.generated.h"

class ATestTaskPlayerState;
class ATestTaskGameMode;
UCLASS()
class ATestTaskHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATestTaskHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

protected:
	//Widget for display score and current wave
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> ScoreWidgetClass;


private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;



};


// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreWidget.h"

#include "TestTaskPlayerState.h"
#include "TestTask/TestTaskGameMode.h"

int32 UScoreWidget::GetScore() const
{
	const auto TestTaskPlayerState = GetTestTaskPlayerState();
	return  TestTaskPlayerState ? TestTaskPlayerState->GetScore() : 0;
}

int32 UScoreWidget::GetCurrentWave() const
{
	const auto TestTaskGameMode = GetTestTaskGameMode();
	return TestTaskGameMode ? TestTaskGameMode->GetCurrentWave() : 0;
}

ATestTaskPlayerState* UScoreWidget::GetTestTaskPlayerState() const
{
	return GetOwningPlayer() ? GetOwningPlayer()->GetPlayerState<ATestTaskPlayerState>() : nullptr;

}

ATestTaskGameMode* UScoreWidget::GetTestTaskGameMode() const
{
	return GetWorld() ? Cast<ATestTaskGameMode>(GetWorld()->GetAuthGameMode()) : nullptr;
}

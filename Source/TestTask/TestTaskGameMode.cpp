// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestTaskGameMode.h"

#include "NavigationSystem.h"
#include "SphereActor.h"
#include "TestTaskCharacter.h"
#include "TestTaskHUD.h"
#include "TestTaskPlayerState.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ATestTaskGameMode::ATestTaskGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestTaskHUD::StaticClass();

	// use our custom PlayerState class
	PlayerStateClass = ATestTaskPlayerState::StaticClass();
}

void ATestTaskGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnSpheres();
}

void ATestTaskGameMode::SpawnSpheres()
{
	if (!GetWorld()) return;
	StartLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();

	//Scale what be changed every sphere
	float CurrentScale = SphereScaleData.StartScale;
	TArray<FVector> SphereLocations;
	
	while (SphereLocations.Num() < QuantityData.QuantityStartSpheres)
	{
		//First spawn spheres in correct radius(RadiusForDestroy), after that spawn other spheres in StartRadius
		const float SpawnLocationX = SphereLocations.Num() <= QuantityData.QuantityOfSpheresForDestroy //
			                       ? FMath::RandRange(StartLocation.X - DistanceData.RadiusForDestroy,
			                                          StartLocation.X + DistanceData.RadiusForDestroy)
			                       : FMath::RandRange(StartLocation.X - DistanceData.StartRadius,
			                                          StartLocation.X + DistanceData.StartRadius
			                       );

		const float SpawnLocationY = SphereLocations.Num() <= QuantityData.QuantityOfSpheresForDestroy //
			                       ? FMath::RandRange(StartLocation.Y - DistanceData.RadiusForDestroy,
			                                          StartLocation.Y + DistanceData.RadiusForDestroy)
			                       : FMath::RandRange(StartLocation.Y - DistanceData.StartRadius,
			                                          StartLocation.Y + DistanceData.StartRadius
			                       );

		FVector SpawnLocation(SpawnLocationX, SpawnLocationY, StartLocation.Z);
		
		//Check distance this location with other spheres 
		if(!CheckDistance(SphereLocations, SpawnLocation)) continue;
		
		//Add this location to correct locations
		SphereLocations.Add(SpawnLocation);

		//Decrease scale, if current is 0.3, minimal is 0.2, step is 0.15 => current will be 0.2(not 0.15 or 0.3)
		CurrentScale = CurrentScale - SphereScaleData.StepDecreasingScale >= SphereScaleData.MinimalScale
			? CurrentScale - SphereScaleData.StepDecreasingScale
			: SphereScaleData.MinimalScale;
	
		const auto Sphere = GetWorld()->SpawnActor<ASphereActor>(SphereToSpawn, SpawnLocation, FRotator());
		Sphere->SetActorScale3D(FVector(CurrentScale));
	
		if(Sphere)
		{
			Sphere->OnSphereDestroy.AddUObject(this, &ATestTaskGameMode::OnSphereDestroy);
		}
	}
}

void ATestTaskGameMode::OnSphereDestroy(const FVector Location)
{
	if (FVector::Dist(Location, StartLocation) <= DistanceData.RadiusForDestroy)
	{
		AddScore();
	}
}

void ATestTaskGameMode::AddScore()
{
	if (!GetWorld()) return;

	const auto Player = Cast<ATestTaskCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player) return;

	const auto PlayerState = Cast<ATestTaskPlayerState>(Player->Controller->PlayerState);
	if (!PlayerState) return;

	//+1 to score
	PlayerState->AddScore();

	CheckScoreToNextWave(PlayerState);
}

void ATestTaskGameMode::CheckScoreToNextWave(ATestTaskPlayerState* PlayerState)
{
	if (PlayerState->GetScore() % QuantityData.QuantityOfSpheresForDestroy == 0)
	{
		PlayerState->ResetScore();
		NextWave();
	}
}

void ATestTaskGameMode::NextWave()
{
	CurrentWave++;
	
	DeleteRestSpheres();
	IncreaseRadiusAndNum();	
	SpawnSpheres();
}

void ATestTaskGameMode::IncreaseRadiusAndNum()
{
	DistanceData.StartRadius *= 1 + IncreaseRadiusPercentEveryRound;
	QuantityData.QuantityStartSpheres *= 1 + IncreaseNumSpherePercentEveryRound;
}

void ATestTaskGameMode::DeleteRestSpheres() const
{
	TArray<AActor*> RestSpheres;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASphereActor::StaticClass(), RestSpheres);
	
	for (const auto RestSphere : RestSpheres)
	{
		RestSphere->Destroy();
	}
}

bool ATestTaskGameMode::CheckDistance(TArray<FVector>& SphereLocations, FVector SpawnLocation) const
{
	for (FVector SphereLoc : SphereLocations)
	{
		if (FVector::Distance(SphereLoc, SpawnLocation) <= DistanceData.MinimalDistanceAmongSphere)
		{
			return false;
		}
	}

	return true;
}

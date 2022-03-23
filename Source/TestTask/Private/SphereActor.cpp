// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereActor.h"
#include "NiagaraFunctionLibrary.h"
#include "TestTask/TestTaskProjectile.h"

// Sets default values
ASphereActor::ASphereActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASphereActor::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ASphereActor::OnOverlapBegin);
}

// Called every frame
void ASphereActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASphereActor::OnOverlapBegin(AActor* Actor, AActor* OtherActor)
{
	if(OtherActor->IsA(ATestTaskProjectile::StaticClass()))
	{
		//Delegate for GameMode logic
		OnSphereDestroy.Broadcast(this->GetActorLocation());

		//Spawn the death effect
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DestroyEffect, GetActorLocation());
		
		Destroy();
		OtherActor->Destroy();
	}
}


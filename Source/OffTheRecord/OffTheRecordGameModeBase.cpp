// Copyright Epic Games, Inc. All Rights Reserved.


#include "OffTheRecordGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnController.h"


AOffTheRecordGameModeBase::AOffTheRecordGameModeBase() : lives(3), score(0), ComboCounter(0)
{


}


void AOffTheRecordGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	Controller->SetShowMouseCursor(false);
}

void AOffTheRecordGameModeBase::StartGame()
{
}


void AOffTheRecordGameModeBase::IncreaseScore()
{
	ComboCounter += 1;
	if (ComboCounter >= 5 && ComboCounter < 10)
	{
		score += 100;
	}
	if (ComboCounter >= 10)
	{
		score += 200;
	}
	score += 100;

}

void AOffTheRecordGameModeBase::SetLives(int32 life)
{
	ComboCounter = 0;
	lives += life;
	if (lives < 0)
	{
		GameOver();
	}
}

void AOffTheRecordGameModeBase::Setup()
{
}

void AOffTheRecordGameModeBase::SpawnEnemy()
{
	TArray<AActor*> ActorsToFind;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ASpawnController::StaticClass(), FName("SpawnControllerTag"), ActorsToFind);

	for (AActor* SpawnControllerActor : ActorsToFind)
	{
		ASpawnController* SpawnController = Cast<ASpawnController>(SpawnControllerActor);
		if (SpawnController) {
			SpawnController->SpawnEnemy();
		}
	}

}

// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "LevelController.h"
#include "SpawnController.h"
#include "BaseCharacter.h"


ALevelController::ALevelController()
{
}

void ALevelController::BeginPlay()
{

}

void ALevelController::SpawnEnemy()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawn LS"));
	SpawnComponent->SpawnEnemy();
}

ABaseCharacter* ALevelController::GetCharacter()
{
	return BaseCharacter;
}


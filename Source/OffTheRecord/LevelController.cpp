// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "LevelController.h"


ALevelController::ALevelController()
{
}

void ALevelController::BeginPlay()
{
	//WorldCamera = GetWorld()->SpawnActor<AWorldCamera>();
	/*
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn) {
		ABaseCharacterPlayerController* PlayerController = Cast<ABaseCharacterPlayerController>(PlayerPawn->GetController());
		if (PlayerController) {
			if (WorldCamera)
			{
				PlayerController->SetViewTargetWithBlend(Cast<AActor>(WorldCamera->GetCam()));
				

			}
		}
	}*/
}

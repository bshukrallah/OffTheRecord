// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "LevelController.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "BaseCharacterPlayerController.h"

ALevelController::ALevelController()
{
	WorldCamera = CreateDefaultSubobject<AActor>(TEXT("World Camera"));
}

void ALevelController::BeginPlay()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn) {
		ABaseCharacterPlayerController* PlayerController = Cast<ABaseCharacterPlayerController>(PlayerPawn->GetController());
		if (PlayerController) {
			if (WorldCamera)
			{
				PlayerController->SetViewTarget(WorldCamera);
			}
		}
	}
}

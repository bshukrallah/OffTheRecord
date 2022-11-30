// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BaseCharacterPlayerController.h"

void ABaseCharacterPlayerController::SetPlayerEnabledState(bool playerEnabled)
{
	if (playerEnabled) {
		GetPawn()->EnableInput(this);
	}
	else GetPawn()->DisableInput(this);
}

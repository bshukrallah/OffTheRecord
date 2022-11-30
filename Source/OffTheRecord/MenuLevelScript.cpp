// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "MenuLevelScript.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

AMenuLevelScript::AMenuLevelScript()
{
}

void AMenuLevelScript::BeginPlay()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	Controller->SetViewTargetWithBlend(MenuCamera);
	Controller->SetShowMouseCursor(true);
}

AActor* AMenuLevelScript::GetMenuCam()
{
	return MenuCamera;
}

AActor* AMenuLevelScript::GetCharacterCam()
{
	return CharacterCamera;
}

// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "MenuLevelScript.h"
#include "GameFramework/Actor.h"

AMenuLevelScript::AMenuLevelScript()
{
}

void AMenuLevelScript::BeginPlay()
{

}

AActor* AMenuLevelScript::GetMenuCam()
{
	return MenuCamera;
}

AActor* AMenuLevelScript::GetCharacterCam()
{
	return CharacterCamera;
}

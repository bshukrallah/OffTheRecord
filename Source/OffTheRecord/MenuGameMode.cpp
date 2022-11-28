// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "MenuGameMode.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MenuLevelScript.h"
#include "Blueprint/UserWidget.h"

AMenuGameMode::AMenuGameMode()
{
}

void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	MenuScript = Cast<AMenuLevelScript>(GetWorld()->GetLevelScriptActor());
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	Controller->SetViewTargetWithBlend(MenuScript->GetMenuCam());

	Controller->SetShowMouseCursor(true);

}
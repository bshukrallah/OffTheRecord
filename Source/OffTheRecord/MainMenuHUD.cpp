// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "MainMenuHUD.h"
#include "Blueprint/UserWidget.h"

AMainMenuHUD::AMainMenuHUD()
{

}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		MainMenu = CreateWidget<UUserWidget>(GetWorld(), MainMenuClass);
	}
	if (MainMenu)
	{
		MainMenu->AddToViewport();
		MainMenu->SetVisibility(ESlateVisibility::Visible);
	}

}

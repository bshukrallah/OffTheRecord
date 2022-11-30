// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class OFFTHERECORD_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
public:
	AMainMenuHUD();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Reference to the Overall HUD Overlay Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UUserWidget> MainMenuClass;

	//Variable to holds the HUD overlay widget after creating it
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widgets, meta = (AllowPrivateAccess = "true"))
		class UUserWidget* MainMenu;
	
};

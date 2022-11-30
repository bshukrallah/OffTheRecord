// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MenuLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class OFFTHERECORD_API AMenuLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	AMenuLevelScript();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class AActor* MenuCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class AActor* CharacterCamera;

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

public:
	UFUNCTION(BlueprintCallable)
		AActor* GetMenuCam();

	UFUNCTION(BlueprintCallable)
		AActor* GetCharacterCam();



};

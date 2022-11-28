// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class OFFTHERECORD_API AMenuGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMenuGameMode();

private:
	class AMenuLevelScript* MenuScript;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
};

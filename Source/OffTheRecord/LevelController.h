// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LevelController.generated.h"

/**
 * 
 */
UCLASS()
class OFFTHERECORD_API ALevelController : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	ALevelController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class AActor* WorldCamera;

public:

	
};

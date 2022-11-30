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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelActors, meta = (AllowPrivateAccess = "true"))
		class ASpawnController* SpawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelActors, meta = (AllowPrivateAccess = "true"))
		class ABaseCharacter* BaseCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:


public:
	void SpawnEnemy();

	class ABaseCharacter* GetCharacter();
	
};

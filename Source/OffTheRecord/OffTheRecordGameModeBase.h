// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OffTheRecordGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class OFFTHERECORD_API AOffTheRecordGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AOffTheRecordGameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	int32 lives;
	int32 score;
	int32 ComboCounter;

public:

	UFUNCTION(BlueprintCallable)
		void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetLives() { return lives; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetScore() { return score; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetCombo() { return ComboCounter; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void ResetComboCounter() { ComboCounter = 0; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void ResetScore() { score = 0; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void ResetLives() { lives = 3; }

	UFUNCTION(BlueprintCallable)
		void IncreaseScore();

	UFUNCTION(BlueprintCallable)
		void SetLives(int32 life);

	UFUNCTION(BlueprintCallable)
		void Setup();

	UFUNCTION(BlueprintCallable)
		void SpawnEnemy();
	
};

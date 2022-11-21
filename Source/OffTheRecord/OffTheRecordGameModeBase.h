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

public:
	
};

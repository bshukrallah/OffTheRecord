// Copyright Epic Games, Inc. All Rights Reserved.


#include "OffTheRecordGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AOffTheRecordGameModeBase::AOffTheRecordGameModeBase()
{


}


void AOffTheRecordGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	Controller->SetShowMouseCursor(false);
}


// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "StatusEnums.h"
#include "AttackTriggerComponent.generated.h"

/**
 * 
 */
UCLASS()
class OFFTHERECORD_API UAttackTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UAttackTriggerComponent();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	bool bCollisionEnabled;

public:
	UFUNCTION(BlueprintCallable, Category = "Collision Settings")
		void DisableCollision();

	UFUNCTION(BlueprintCallable, Category = "Collision Settings")
		void EnableCollision();
	
};

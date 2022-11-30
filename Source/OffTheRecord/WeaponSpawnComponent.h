// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponSpawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OFFTHERECORD_API UWeaponSpawnComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponSpawnComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ABaseWeapon> Guitar1;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ABaseWeapon> Guitar2;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ABaseWeapon> Guitar3;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ABaseWeapon> BaseballBat;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ABaseWeapon> Hammer1;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ABaseWeapon> Hammer2;

	UPROPERTY()
		class ABaseWeapon* WeaponToSpawn;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SpawnWeapon();

		
};

// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "WeaponSpawnComponent.h"
#include "BaseWeapon.h"

// Sets default values for this component's properties
UWeaponSpawnComponent::UWeaponSpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWeaponSpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponSpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponSpawnComponent::SpawnWeapon()
{
	int32 WeaponSpawn = FMath::RandRange(10, 20);

	if (WeaponSpawn <= 14) { return; }

	switch (WeaponSpawn) {

	case 15:
		WeaponToSpawn = GetWorld()->SpawnActor<ABaseWeapon>(Guitar1, GetRelativeLocation(), GetRelativeRotation());
		break;

	case 16:
		WeaponToSpawn = GetWorld()->SpawnActor<ABaseWeapon>(Guitar2, GetRelativeLocation(), GetRelativeRotation());
		break;

	case 17:
		WeaponToSpawn = GetWorld()->SpawnActor<ABaseWeapon>(Guitar3, GetRelativeLocation(), GetRelativeRotation());
		break;

	case 18:
		WeaponToSpawn = GetWorld()->SpawnActor<ABaseWeapon>(BaseballBat, GetRelativeLocation(), GetRelativeRotation());
		break;

	case 19:
		WeaponToSpawn = GetWorld()->SpawnActor<ABaseWeapon>(Hammer1, GetRelativeLocation(), GetRelativeRotation());
		break;

	case 20:
		WeaponToSpawn = GetWorld()->SpawnActor<ABaseWeapon>(Hammer2, GetRelativeLocation(), GetRelativeRotation());
	}

}


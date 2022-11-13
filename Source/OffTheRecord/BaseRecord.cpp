#include "BaseRecord.h"

// Sets default values
ABaseRecord::ABaseRecord()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpinValue = 0.f;
}

// Called when the game starts or when spawned
void ABaseRecord::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseRecord::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator NewRotation = FRotator(0.f, SpinValue, 0.f);
	FQuat QuatRotation = FQuat(NewRotation);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}


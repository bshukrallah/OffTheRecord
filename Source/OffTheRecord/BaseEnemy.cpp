// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BaseEnemy.h"
#include "HitColliderComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrontHitBox = CreateDefaultSubobject<UHitColliderComponent>(TEXT("Front Hit Box"));
	FrontHitBox->SetupAttachment(GetRootComponent());

	BackHitBox = CreateDefaultSubobject<UHitColliderComponent>(TEXT("Back Hit Box"));
	BackHitBox->SetupAttachment(GetRootComponent());

	TopHitBox = CreateDefaultSubobject<UHitColliderComponent>(TEXT("Top Hit Box"));
	TopHitBox->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


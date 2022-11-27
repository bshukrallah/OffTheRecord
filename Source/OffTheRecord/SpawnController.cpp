// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "SpawnController.h"
#include "BaseCharacter.h"
#include "BaseEnemy.h"
#include "BaseWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "WeaponSpawnComponent.h"

// Sets default values
ASpawnController::ASpawnController() : bReadyToSpawn(true), NumberOfEnemies(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DeathBoundary = CreateDefaultSubobject<USphereComponent>(TEXT("Death Boundary"));
	DeathBoundary->SetCollisionResponseToAllChannels(ECR_Overlap);
	DeathBoundary->SetRelativeScale3D(FVector(37.0f, 37.0f, 37.0f));
	DeathBoundary->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	FogBoundary = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fog Boundary"));
	FogBoundary->SetCollisionResponseToAllChannels(ECR_Ignore);
	FogBoundary->SetRelativeScale3D(FVector(30.0f, 30.0f, 30.0f));
	FogBoundary->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	SpawnPoint1 = CreateDefaultSubobject<USphereComponent>(TEXT("Spawn Point 1"));
	SpawnPoint1->SetupAttachment(GetRootComponent());
	SpawnPoint1->SetCollisionResponseToAllChannels(ECR_Ignore);

	SpawnPoint2 = CreateDefaultSubobject<USphereComponent>(TEXT("Spawn Point 2"));
	SpawnPoint2->SetupAttachment(GetRootComponent());
	SpawnPoint2->SetCollisionResponseToAllChannels(ECR_Ignore);

	SpawnPoint3 = CreateDefaultSubobject<USphereComponent>(TEXT("Spawn Point 3"));
	SpawnPoint3->SetupAttachment(GetRootComponent());
	SpawnPoint3->SetCollisionResponseToAllChannels(ECR_Ignore);

	SpawnPoint4 = CreateDefaultSubobject<USphereComponent>(TEXT("Spawn Point 4"));
	SpawnPoint4->SetupAttachment(GetRootComponent());
	SpawnPoint4->SetCollisionResponseToAllChannels(ECR_Ignore);

	SpawnPoint5 = CreateDefaultSubobject<USphereComponent>(TEXT("Spawn Point 5"));
	SpawnPoint5->SetupAttachment(GetRootComponent());
	SpawnPoint5->SetCollisionResponseToAllChannels(ECR_Ignore);

	SpawnPoint6 = CreateDefaultSubobject<USphereComponent>(TEXT("Spawn Point 6"));
	SpawnPoint6->SetupAttachment(GetRootComponent());
	SpawnPoint6->SetCollisionResponseToAllChannels(ECR_Ignore);

	WeaponSpawn1 = CreateDefaultSubobject<UWeaponSpawnComponent>(TEXT("Weapon Spawn Point 1"));
	WeaponSpawn1->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASpawnController::BeginPlay()
{
	Super::BeginPlay();


	DeathBoundary->OnComponentBeginOverlap.AddDynamic(this, &ASpawnController::OnOverlap);
	DeathBoundary->OnComponentEndOverlap.AddDynamic(this, &ASpawnController::OnEndOverlap);
}

// Called every frame
void ASpawnController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bReadyToSpawn)
	{
		bReadyToSpawn = false;
		AutoSpawnHandler();
		WeaponSpawn1->SpawnWeapon();
	}

}

void ASpawnController::AutoSpawnHandler()
{
	FTimerHandle AutoSpawnTimer;
	GetWorldTimerManager().SetTimer(AutoSpawnTimer, this, &ASpawnController::SpawnEnemy, 20.f, false);
}

void ASpawnController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ASpawnController::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))
	{
		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OtherActor);
		if (OtherComp == BaseCharacter->GetCapsuleComponent())
		{
			BaseCharacter->Death();
		};
	}
	if (OtherActor->GetClass()->IsChildOf(ABaseEnemy::StaticClass()))
	{
		ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(OtherActor);
		if (OtherComp == BaseEnemy->GetCapsuleComponent())
		{
			BaseEnemy->Death();
			NumberOfEnemies--;
			SpawnEnemy();
		};
	}

	if (OtherActor->GetClass()->IsChildOf(ABaseWeapon::StaticClass()))
	{
		ABaseWeapon* Weapon = Cast<ABaseWeapon>(OtherActor);
		if (Weapon) {
			//Weapon->Destroy();
		}
	}
}

void ASpawnController::SpawnEnemy()
{
	if (NumberOfEnemies >= 8) return;
	int32 NumberToSpawn = FMath::RandRange(1, 2);
	for (int x = 0; x < NumberToSpawn; x++)
	{
		int32 SpawnPoint = FMath::RandRange(1, 5);
		if (LastSpawnPoint == SpawnPoint) {
			SpawnPoint = 6;
		}
		switch (SpawnPoint) {
		case 1:
			EnemyToSpawn = GetWorld()->SpawnActor<ABaseEnemy>(Enemy, SpawnPoint1->GetRelativeLocation(), SpawnPoint1->GetRelativeRotation());
			break;

		case 2:
			EnemyToSpawn = GetWorld()->SpawnActor<ABaseEnemy>(Enemy, SpawnPoint2->GetRelativeLocation(), SpawnPoint2->GetRelativeRotation());
			break;

		case 3:
			EnemyToSpawn = GetWorld()->SpawnActor<ABaseEnemy>(Enemy, SpawnPoint3->GetRelativeLocation(), SpawnPoint3->GetRelativeRotation());
			break;

		case 4:
			EnemyToSpawn = GetWorld()->SpawnActor<ABaseEnemy>(Enemy, SpawnPoint4->GetRelativeLocation(), SpawnPoint4->GetRelativeRotation());
			break;

		case 5:
			EnemyToSpawn = GetWorld()->SpawnActor<ABaseEnemy>(Enemy, SpawnPoint5->GetRelativeLocation(), SpawnPoint6->GetRelativeRotation());
			break;

		case 6:
			EnemyToSpawn = GetWorld()->SpawnActor<ABaseEnemy>(Enemy, SpawnPoint6->GetRelativeLocation(), SpawnPoint6->GetRelativeRotation());
		}
		LastSpawnPoint = SpawnPoint;
		NumberOfEnemies++;
	}
	bReadyToSpawn = true;

}

